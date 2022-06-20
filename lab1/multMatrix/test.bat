@echo off



set PROGRAM="%~1"
set OUT="%TEMP%\out.txt"
echo %PROGRAM%

%PROGRAM% 0Matrix.txt 0Matrix.txt > %OUT% 
if ERRORLEVEL 1 goto err
fc 0Matrix.txt %OUT% 
if ERRORLEVEL 1 goto err

%PROGRAM% 1Matrix.txt 0Matrix.txt > %OUT%
if ERRORLEVEL 1 goto err
fc %OUT% 0Matrix.txt
if ERRORLEVEL 1 goto err

%PROGRAM% a.txt b.txt > %OUT%
if ERRORLEVEL 1 goto err
fc %OUT% c.txt
if ERRORLEVEL 1 goto err

%PROGRAM% a.txt b.txt > %OUT%
if ERRORLEVEL 1 goto err
fc %OUT% c.txt
if ERRORLEVEL 1 goto err

%PROGRAM% incorrectmatrix.txt 1Matrix.txt > %OUT%
if NOT ERRORLEVEL 1 goto err
fc %OUT% expected-output-when-input-file-is-missing.txt 
if ERRORLEVEL 1 goto err

%PROGRAM% incorrectmatrix2.txt 1Matrix.txt > %OUT%
if NOT ERRORLEVEL 1 goto err
fc %OUT% expected-output-when-input-file-is-missing.txt 
if ERRORLEVEL 1 goto err

%PROGRAM% non-existing-file-name.txt 1Matrix.txt > %OUT%
if NOT ERRORLEVEL 1 goto err
fc %OUT% expected-output-when-input-file-is-missing.txt 
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit /B 0

:err
echo Program test failed
exit /B 1
