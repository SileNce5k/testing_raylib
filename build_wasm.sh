#!/bin/sh

set -xe

emcc -o game.html main.c -Os -Wall ./html/src/libraylib.a -I. -I ./html/src/raylib.h -L. -L ./html/src/libraylib.a -s USE_GLFW=3 -s ASYNCIFY --shell-file ./html/src/minshell.html -DPLATFORM_WEB
