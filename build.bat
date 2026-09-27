@echo off

py -3 configure.py --kamek F:\WiiToolchain\KamekBuild --cw F:\WiiToolchain\cw

if exist .\_maps rmdir /S /Q .\_maps
if exist .\_build rmdir /S /Q .\_build
if exist .\bin rmdir /S /Q .\bin

F:\WiiToolchain\ninja.exe

robocopy ^
    ".\bin" ^
    "%USERPROFILE%\AppData\Roaming\Dolphin Emulator\Load\PADV\Code" ^
    /E

exit /B 0