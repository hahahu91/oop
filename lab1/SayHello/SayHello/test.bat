@echo off

set PROGRAM="%~1"
set OUT="%TEMP%\out.txt"

%PROGRAM%  < Boris.txt > %OUT% || goto err
fc %OUT% Boris-out.txt || goto err

%PROGRAM%  < HarryPotter.txt > %OUT% || goto err
fc %OUT% HarryPotter-out.txt || goto err

%PROGRAM%  < Empty.txt > %OUT% || goto err
fc %OUT% Empty-out.txt || goto err

echo All test passed!
exit /B 0

:err
echo Test failed!
exit /B 1


