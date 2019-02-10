@echo off

set PROGRAM="%~1"
echo %PROGRAM%

%PROGRAM%  Empty.txt %TEMP%/Empty-out.txt || goto err
fc Empty.txt %TEMP%/Empty-out.txt || goto err

%PROGRAM%  OneLine.txt %TEMP%/OneLine-out.txt || goto err
fc OneLine.txt %TEMP%/OneLine-out.txt || goto err

%PROGRAM% multiline.txt %TEMP%\multiline.txt
if ERRORLEVEL 1 goto err

fc %TEMP%\multiline.txt multiline.txt
if ERRORLEVEL 1 goto err


%PROGRAM% non-existing-file-name.txt %TEMP%\non-existing-file-name.txt > "%TEMP%\output.txt"
if NOT ERRORLEVEL 1 goto err

fc %TEMP%\output.txt expected-output-when-input-file-is-missing.txt 
if ERRORLEVEL 1 goto err

%PROGRAM% multiline.txt %PROGRAM% > %TEMP%\output.txt
if NOT ERRORLEVEL 1 goto err

fc %TEMP%\output.txt expected-output-when-output-error-file.txt 
if ERRORLEVEL 1 goto err

echo Program testing succeeded
exit /B 0

:err
echo Program test failed
exit /B 1
