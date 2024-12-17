:: Copyright (C) Avnish Kirnalli 2024.

@echo off

@echo off & title Generate New Project

goto :DOES_PYTHON_EXIST

:DOES_PYTHON_EXIST
python -V | find /v "Python" >NUL 2>NUL && (goto :PYTHON_DOES_NOT_EXIST)
python -V | find "Python"    >NUL 2>NUL && (goto :PYTHON_DOES_EXIST)
goto :EOF

:PYTHON_DOES_NOT_EXIST
echo Python is not installed on your system.
echo Now opening the download URL.
start "" "https://www.python.org/downloads/windows/"
goto :EOF

:PYTHON_DOES_EXIST
python GenerateNewProject.py

:EOF
