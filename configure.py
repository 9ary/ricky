#!/usr/bin/env python3

import shogun

obj = shogun.Objects("src/*.cpp", "cxx", "o")
exe = shogun.Assembly("$builddir/ricky", "cxxld", obj,
        options = { "libs": "-lGLEW -lGL -lsfml-system -lsfml-window -lsfml-graphics" })

shogun.build(obj, exe)
