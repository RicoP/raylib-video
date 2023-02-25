@echo off

setlocal EnableDelayedExpansion

set "vswhere=%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe"
set "install_path="

for /f "usebackq tokens=*" %%i in (`"!vswhere!" -latest -prerelease -requires Microsoft.VisualStudio.Component.VC.Tools.x86.x64 -property installationPath`) do (
    set "install_path=%%i"
)

if defined install_path (
    echo Setting up compile environment...
    call "!install_path!\VC\Auxiliary\Build\vcvarsall.bat" x64
) else (
    echo Error: MSVC build tools not found.
    echo Please install Visual Studio Community
    exit /b 1
)

CL /TC /Ox /DGRAPHICS_API_OPENGL_33 /DPLATFORM_DESKTOP ^
   /Iraylib/src ^
   /Iraylib/src/external ^
   /Iraylib/src/external/glfw/include ^
   /Iraylib/src/external/glfw/deps ^
   /Ipl_mpeg ^
   /I../include ^
   example.c raylib/src/*.c ^
   /link user32.lib shell32.lib winmm.lib gdi32.lib

DEL *.exp *.lib *.obj

example.exe
