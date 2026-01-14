@echo off

setlocal enableextensions enabledelayedexpansion

set "VER="
for /f "tokens=3" %%a in ('findstr /r /c:"#define[ ]\+APP_VERSION" src\app.h') do set "VER=%%a"

if "%VER%"=="" (
	echo Failed to read APP_VERSION from src\app.h
	goto end
)

set "VER=!VER:L=\"=!"
set "VER=!VER:\"=!"

cd builder
call build simplewall !VER! simplewall

:end
pause
