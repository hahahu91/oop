@echo off

set PROGRAM="%~1"
set OUT="%TEMP%\out.txt"

%PROGRAM% Empty.txt > %OUT%
if ERRORLEVEL 1 goto err

fc %OUT% Empty.txt 
if ERRORLEVEL 1 goto err

%PROGRAM% correctNumbers.txt > %OUT%
if ERRORLEVEL 1 goto err

fc %OUT% correctNumbers-out.txt
if ERRORLEVEL 1 goto err

%PROGRAM% correctNumbers2.txt > %OUT%
if ERRORLEVEL 1 goto err

fc %OUT% correctNumbers2-out.txt
if ERRORLEVEL 1 goto err

%PROGRAM% notCorrectNumbers.txt > %OUT%
if NOT ERRORLEVEL 1 goto err
fc %OUT% readingError.txt 
if ERRORLEVEL 1 goto err

echo Program test succesed
exit /B 0

:err
echo Program test failed
exit /B 1