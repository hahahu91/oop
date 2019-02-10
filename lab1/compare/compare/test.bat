@echo off

set PROGRAM="%~1"
set OUT="%TEMP%\out.txt"

%PROGRAM% Empty.txt Empty2.txt > %OUT%
if ERRORLEVEL 1 goto err

fc %OUT% equal-out.txt 
if ERRORLEVEL 1 goto err

%PROGRAM% Text1.txt Text1-copy.txt > %OUT%
if ERRORLEVEL 1 goto err

fc %OUT% equal-out.txt 
if ERRORLEVEL 1 goto err

%PROGRAM% Text1.txt Text1-different-line3.txt > %OUT%
if ERRORLEVEL 1 goto err

fc %OUT% different-out-line3.txt 
if ERRORLEVEL 1 goto err

%PROGRAM% non-existing-file-name.txt Text1.txt > %OUT%
if NOT ERRORLEVEL 1 goto err

fc %OUT% failed-open-file.txt 
if ERRORLEVEL 1 goto err

echo Program test succesed
exit /B 0

:err
echo Program test failed
exit /B 1