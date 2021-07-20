@echo off
if not exist "%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" ( echo "ERROR: VS2017 not found" )
for /f "tokens=*" %%a in ('"%ProgramFiles(x86)%\Microsoft Visual Studio\Installer\vswhere.exe" -property productPath') do set devenv=%%a
"%devenv:~0,-4%.com" .\build\SimOneIOAPISample.sln /build Debug
pause
if %ERRORLEVEL% GEQ 1 EXIT /B 1