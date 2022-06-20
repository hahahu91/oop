@echo off

set PROGRAM="%~1"
set OUT="%TEMP%\out.txt"

%PROGRAM% pack Input.txt Output.txt > %OUT%
if ERRORLEVEL 1 goto err

echo Program test succesed
exit /B 0

:err
echo Program test failed
exit /B 1