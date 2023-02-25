CL /TC /Ox /DGRAPHICS_API_OPENGL_33 /DPLATFORM_DESKTOP ^
   /I../raylib/src ^
   /I../raylib/src/external ^
   /I../raylib/src/external/glfw/include ^
   /I../raylib/src/external/glfw/deps ^
   /I../pl_mpeg ^
   /I../../include ^
   example.c ../raylib/src/*.c ^
   /link user32.lib shell32.lib winmm.lib gdi32.lib

DEL *.exp *.lib *.obj

example.exe