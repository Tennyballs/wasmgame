#!/bin/bash
emcc ./src/main.c -sFULL_ES2 -sUSE_GLFW=2 -lglfw -sMAX_WEBGL_VERSION=2 -sWASM=1 -o build/main.html \
--preload-file src/assets
