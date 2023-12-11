#!/usr/bin/env bash
set -e
# Build the project
if [ -z "${RAYLIB_PATH}" ]; then
    echo "RAYLIB_PATH is not set. Please set it and rerun the script."
    exit 1
fi
echo Compiling main.c
gcc -o main main.c      common_functions.c -L${RAYLIB_PATH} -lraylib -lgdi32 -lwinmm
echo Compiling other.c
gcc -o other other.c    common_functions.c -L${RAYLIB_PATH} -lraylib -lgdi32 -lwinmm
echo Compiling game.c
gcc -o game game.c common_functions.c -L${RAYLIB_PATH} -lraylib -lgdi32 -lwinmm
