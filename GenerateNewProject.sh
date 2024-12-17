#!/bin/sh
# Copyright (C) Avnish Kirnalli 2024.

# Check for python3 or fallback to python
if command -v python3 &>/dev/null; then
    PYTHON_EXEC="python3"
elif command -v python &>/dev/null; then
    PYTHON_EXEC="python"
else
    echo "Python is not installed. Please install Python (https://www.python.org) before running this script."
    exit 1
fi

cd "$(dirname "$0")"
$PYTHON_EXEC GenerateNewProject.py