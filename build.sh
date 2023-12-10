#!/usr/bin/env bash
set -e
# Build the project
if [ -z "${RAYLIB_PATH}" ]; then
    echo "RAYLIB_PATH is not set. Please set it and rerun the script."
    exit 1
fi
gcc -o main main.c -L${RAYLIB_PATH} -lraylib -lgdi32 -lwinmm
