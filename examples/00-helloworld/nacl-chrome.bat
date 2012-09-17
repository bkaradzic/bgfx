@echo off
setlocal
set NACL_DEBUG=%~dp0..\..\.debug\nacl
set NACL_EXE_STDERR=%NACL_DEBUG%\stderr.txt
set NACL_EXE_STDOUT=%NACL_DEBUG%\stdout.txt
set NACL_DANGEROUS_ENABLE_FILE_ACCESS=1
mkdir %NACL_DEBUG% > nul
rm -rf %NACL_EXE_STDERR% > nul
rm -rf %NACL_EXE_STDOUT% > nul
start %LOCALAPPDATA%\Google\Chrome\Application\chrome.exe --incognito --no-sandbox --show-fps-counter http://localhost:8080 %*
