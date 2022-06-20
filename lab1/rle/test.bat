@echo off

set PROGRAM="%~1"
set OUT="%TEMP%\out.txt"
set OUT1="%TEMP%\out1.txt"
echo %PROGRAM%


%PROGRAM% pack Input.txt %OUT%
if ERRORLEVEL 1 goto err
fc Output1.txt %OUT%
if ERRORLEVEL 1 goto err

%PROGRAM% unpack Output1.txt %OUT1%
if ERRORLEVEL 1 goto err
fc Input.txt %OUT1%
if ERRORLEVEL 1 goto err


echo Program testing succeeded
exit /B 0

:err
echo Program test failed
exit /B 1
