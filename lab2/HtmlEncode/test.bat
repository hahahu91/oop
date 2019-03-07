@echo off

set PROGRAM="%~1"
set OUT="%TEMP%\out.txt"

%PROGRAM% Empty.txt > %OUT%
if ERRORLEVEL 1 goto err

fc %OUT% Empty-out.txt 
if ERRORLEVEL 1 goto err

%PROGRAM% input1.txt > %OUT%
if ERRORLEVEL 1 goto err

fc %OUT% input1-out.txt
if ERRORLEVEL 1 goto err

echo Program test succesed
exit /B 0

:err
echo Program test failed
exit /B 1