@echo off
REM ============================================================
REM  Builds SH3GraphicsSaver.asi (32-bit) using Visual Studio 2019.
REM  Run this file by double-clicking it. No arguments needed.
REM ============================================================
setlocal
set "SRCDIR=%~dp0"

set "VSDEV=C:\Program Files (x86)\Microsoft Visual Studio\2019\Community\VC\Auxiliary\Build\vcvarsall.bat"
if not exist "%VSDEV%" (
    echo Could not find Visual Studio 2019 C++ tools at:
    echo   "%VSDEV%"
    echo Install "Desktop development with C++" or edit this path.
    pause
    exit /b 1
)

REM vcvarsall changes the current directory, so call it first, THEN cd back.
call "%VSDEV%" x86
cd /d "%SRCDIR%"

REM Clean any previous output, then compile as a 32-bit DLL named .asi.
if exist "SH3GraphicsSaver.asi" del "SH3GraphicsSaver.asi"
cl /nologo /LD /EHsc /O2 /MT dllmain.cpp /link /DLL /OUT:SH3GraphicsSaver.asi /SUBSYSTEM:WINDOWS

if not exist "SH3GraphicsSaver.asi" (
    echo.
    echo BUILD FAILED.
    pause
    exit /b 1
)

echo.
echo BUILD OK. Output file: SH3GraphicsSaver.asi
echo.
echo Copying to the game folder...
copy /y "SH3GraphicsSaver.asi" "..\SH3GraphicsSaver.asi" >nul
copy /y "SH3GraphicsSaver.ini" "..\SH3GraphicsSaver.ini" >nul
echo Done. SH3GraphicsSaver.asi and .ini are now next to sh3.exe.
echo.
pause
endlocal
