#!/usr/bin/env python3

import shogun

obj = shogun.Objects("src/*.cpp", "cxx", "o", "$builddir")
asm = shogun.Assembly("ricky", "cxxld", [obj],
        options = { "libs": "-lGLEW -lGL -lsfml-system -lsfml-window -lsfml-graphics" })

with open("targets.ninja", "w") as f:
    shogun.save(f, [obj, asm])
