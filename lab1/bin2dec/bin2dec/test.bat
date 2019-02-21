@echo off

set PROGRAM="%~1"
set OUT="%TEMP%\out.txt"

%PROGRAM%  11100100 > %OUT%
if ERRORLEVEL 1 goto err

fc %OUT% 228out.txt
if ERRORLEVEL 1 goto err

%PROGRAM%  1111111111111010 > %OUT%
if ERRORLEVEL 1 goto err

fc %OUT% 65530out.txt
if ERRORLEVEL 1 goto err

%PROGRAM%  228 > %OUT%
if NOT ERRORLEVEL 1 goto err

fc %OUT% errorNumber.txt
if ERRORLEVEL 1 goto err

echo Program test succesed
exit /B 0

:err
echo Program test failed
exit /B 1
