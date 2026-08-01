@echo off
setlocal
cd /d "%~dp0"

REM ============================================================
REM  Silent Hill 3 - Save Graphics Settings launcher
REM
REM  Forces "Real-Time Shadow" and "Lens Flare Quality" into
REM  savedata\disp.ini right before the game starts, so they
REM  don't reset to OFF/Fast every time you launch the game.
REM
REM  Edit the two values below, then run this file to play.
REM    1 = ON  / Detail  (higher quality)
REM    0 = OFF / Fast    (better performance)
REM ============================================================

set "SHADOW=0"
set "LENSFLARE=0"

set "DISP=savedata\disp.ini"

if not exist "%DISP%" (
    echo Could not find "%DISP%".
    echo Make sure this .bat file is in your Silent Hill 3 folder.
    pause
    exit /b 1
)

REM Update the two keys in disp.ini, preserving every other setting.
powershell -NoProfile -ExecutionPolicy Bypass -Command "$f='%DISP%'; $c=@(Get-Content -LiteralPath $f); if($c -match '^shadow='){$c=$c -replace '^shadow=.*','shadow=%SHADOW%'}else{$c+='shadow=%SHADOW%'}; if($c -match '^lensflare_ztest='){$c=$c -replace '^lensflare_ztest=.*','lensflare_ztest=%LENSFLARE%'}else{$c+='lensflare_ztest=%LENSFLARE%'}; Set-Content -LiteralPath $f -Value $c"

echo Applied graphics settings:
echo    Real-Time Shadow  = %SHADOW%
echo    Lens Flare Quality = %LENSFLARE%
echo.

REM Launch the game (tries the common executable names).
if exist "sh3.exe" (
    start "" "sh3.exe"
) else if exist "silent hill 3.exe" (
    start "" "silent hill 3.exe"
) else (
    echo Could not find the game executable ^(sh3.exe^).
    echo Launch the game manually - your settings are already applied.
    pause
    exit /b 1
)

endlocal
