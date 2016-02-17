from glob import glob
import os

def lookahead(iterable):
    it  = iter(iterable)
    last = next(it)
    for val in it:
        yield last, False
        last = val
    yield last, True

class Objects:
    def __init__(self, pathname, rule, extout, outdir = "", recursive = False):
        self.files = glob(pathname, recursive = recursive)
        self.pathname = pathname
        self.extout = "." + extout
        self.outdir = outdir
        self.rule = rule

    def objs(self):
        for f in self.files:
            outf = os.path.join(self.outdir, os.path.splitext(f)[0] + self.extout)
            yield outf

    def targets(self):
        yield "# {} {}".format(self.rule, self.pathname)
        for f in self.files:
            outf = os.path.join(self.outdir, os.path.splitext(f)[0] + self.extout)
            yield "build {}: {} {}".format(outf, self.rule, f)

class Assembly:
    def __init__(self, path, rule, objects, outdir = "", options = {}):
        self.path = os.path.join(outdir, path)
        self.rule = rule
        self.objects = objects
        self.options = options

    def objs(self):
        yield self.path

    def targets(self):
        yield "# {} {}".format(self.rule, self.path)
        yield "build {}: {} $".format(self.path, self.rule)

        for os, lastos in lookahead(self.objects):
            for o, lasto in lookahead(os.objs()):
                if not(lastos and lasto):
                    yield "    {} $".format(o)
                else:
                    yield "    {}".format(o)

        for o in self.options:
            yield "    {} = {}".format(o, self.options[o])

def save(fd, targets):
    for t in targets:
        for l in t.targets():
            fd.write(l + "\n")
        fd.write("\n")
