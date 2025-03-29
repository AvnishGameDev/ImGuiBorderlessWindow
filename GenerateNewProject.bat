:: Copyright (C) Avnish Kirnalli 2025.

@echo off & title Generate New Project

setlocal

:: Check for python3
python3 --version >nul 2>&1
if %errorlevel% equ 0 (
    set "PYTHON_CMD=python3"
    goto CHECK_VENV
)

:: Check for python (fallback)
python --version >nul 2>&1
if %errorlevel% equ 0 (
    set "PYTHON_CMD=python"
    goto CHECK_VENV
)

:: Neither python3 nor python is installed
echo Python is not installed or not in your PATH.
echo Please install Python from https://www.python.org/downloads/windows and try again.
pause
exit /b 1

:CHECK_VENV
:: Check if virtual environment exists, if not create it
if not exist ".python" (
    echo Creating virtual environment...
    %PYTHON_CMD% -m venv .python
)

:: Activate virtual environment
if exist ".python\Scripts\activate.bat" (
    call .python\Scripts\activate.bat
) else (
    echo Error: Virtual environment activation script not found
    pause
    exit /b 1
)

echo Using %PYTHON_CMD% in virtual environment on Windows
%PYTHON_CMD% GenerateNewProject.py %PYTHON_CMD%

:: Deactivate virtual environment when done
deactivate