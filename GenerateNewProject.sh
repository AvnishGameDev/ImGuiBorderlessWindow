#!/usr/bin/env bash
# Copyright (C) Avnish Kirnalli 2025.

set -euo pipefail  # Exit on error, undefined variables, and pipe failures

# Function to print error messages
error() {
    echo "Error: $1" >&2
    exit 1
}

# Function to print status messages
status() {
    echo "Status: $1"
}

# Detect OS
case "$(uname -s)" in
    Darwin)     OS="MacOS";;
    Linux)      OS="Linux";;
    *)          error "Unsupported operating system: $(uname -s)";;
esac

# Find Python executable
if command -v python3 >/dev/null 2>&1; then
    PYTHON_EXEC="python3"
elif command -v python >/dev/null 2>&1; then
    PYTHON_EXEC="python"
else
    error "Python is not installed. Please install Python (https://www.python.org) before running this script."
fi

# Get script directory
SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
cd "$SCRIPT_DIR"

# Create virtual environment if it doesn't exist
if [ ! -d "venv" ]; then
    status "Creating virtual environment..."
    if ! $PYTHON_EXEC -m venv venv; then
        error "Failed to create virtual environment"
    fi
fi

# Activate virtual environment
if [ ! -f "venv/bin/activate" ]; then
    error "Virtual environment activation script not found"
fi

# Activate the virtual environment
source venv/bin/activate

# Verify we're in the virtual environment
if [ -z "${VIRTUAL_ENV:-}" ]; then
    error "Failed to activate virtual environment"
fi

status "Using $PYTHON_EXEC in virtual environment on $OS"

# Run the Python script
if ! $PYTHON_EXEC GenerateNewProject.py "$PYTHON_EXEC"; then
    error "Python script failed"
fi

# Deactivate virtual environment
deactivate

status "Script completed successfully"