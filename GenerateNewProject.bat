:: Copyright (C) Avnish Kirnalli 2024.

@echo off & title Generate New Project

setlocal

:: Check for python3
python3 --version >nul 2>&1
if %errorlevel% equ 0 (
    set "PYTHON_CMD=python3"
    goto RUN_SCRIPT
)

:: Check for python (fallback)
python --version >nul 2>&1
if %errorlevel% equ 0 (
    set "PYTHON_CMD=python"
    goto RUN_SCRIPT
)

:: Neither python3 nor python is installed
echo Python is not installed or not in your PATH.
echo Please install Python from https://www.python.org/downloads/windows and try again.
pause
exit /b 1

:RUN_SCRIPT
%PYTHON_CMD% GenerateNewProject.py