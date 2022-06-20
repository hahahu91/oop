@echo off

set PROGRAM="%~1"
set OUT="%TEMP%\out.txt"

%PROGRAM%  255 > %OUT%
if ERRORLEVEL 1 goto err

fc %OUT% 255out.txt
if ERRORLEVEL 1 goto err

%PROGRAM%  0 > %OUT%
if ERRORLEVEL 1 goto err

fc %OUT% 0out.txt
if ERRORLEVEL 1 goto err

%PROGRAM%  15 > %OUT%
if ERRORLEVEL 1 goto err

fc %OUT% 15out.txt
if ERRORLEVEL 1 goto err

%PROGRAM%  -1 > %OUT%
if NOT ERRORLEVEL 1 goto err

fc %OUT% "-15out.txt"
if ERRORLEVEL 1 goto err

%PROGRAM%  256 > %OUT%
if NOT ERRORLEVEL 1 goto err

fc %OUT% "-15out.txt"
if ERRORLEVEL 1 goto err

%PROGRAM%  -15 > %OUT%
if NOT ERRORLEVEL 1 goto err

fc %OUT% "-15out.txt"
if ERRORLEVEL 1 goto err

%PROGRAM%  65555555 > %OUT%
if NOT ERRORLEVEL 1 goto err

fc %OUT% "-15out.txt"
if ERRORLEVEL 1 goto err

%PROGRAM%  Text > %OUT%
if NOT ERRORLEVEL 1 goto err

fc %OUT% "Text-out.txt"
if ERRORLEVEL 1 goto err

echo Program test succesed
exit /B 0

:err
echo Program test failed
exit /B 1
