@echo off
call "C:\Program Files (x86)\Microsoft Visual Studio\2022\BuildTools\Common7\Tools\VsDevCmd.bat" -no_logo -arch=amd64 -host_arch=amd64
cl /nologo /c routine\src\routine.c
