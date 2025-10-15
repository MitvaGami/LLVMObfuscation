#!/bin/bash
echo "Fixing CMake cache issue..."

# Navigate to the project directory
cd /home/mohini/LLVMObfuscation

# Clean and recreate build directory
echo "Cleaning build directory..."
rm -rf build
mkdir build

# Configure with CMake
echo "Configuring with CMake..."
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release

# Build the project
echo "Building project..."
cmake --build build

echo "Done!"
