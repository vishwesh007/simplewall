@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat" -no_logo -arch=amd64 -host_arch=amd64
echo WindowsSDKDir=%WindowsSDKDir%
echo WindowsSDKVersion=%WindowsSDKVersion%
echo INCLUDE=%INCLUDE%
echo LIB=%LIB%
