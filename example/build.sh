#!/bin/sh

gcc -O3 -D GRAPHICS_API_OPENGL_33 -D PLATFORM_DESKTOP \
   -Iraylib/src \
   -Iraylib/src/external \
   -Iraylib/src/external/glfw/include \
   -Iraylib/src/external/glfw/deps \
   -Ipl_mpeg \
   -I../include \
   example.c raylib/src/*.c \
   -luser32 -lshell32 -lwinmm -lgdi32 -lpthread -o example.exe

