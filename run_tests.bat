@echo off
setlocal
cd /d "%~dp0"
where g++ >nul 2>nul
if errorlevel 1 (
  echo ERROR: g++ was not found. Install a C++ compiler and add it to PATH.
  exit /b 1
)
if not exist data mkdir data
g++ -std=c++17 -Wall -Wextra -pedantic tests/test_leaderboard.cpp -o tests\test_leaderboard.exe
if errorlevel 1 exit /b 1
tests\test_leaderboard.exe
set RESULT=%ERRORLEVEL%
del tests\test_leaderboard.exe >nul 2>nul
exit /b %RESULT%
