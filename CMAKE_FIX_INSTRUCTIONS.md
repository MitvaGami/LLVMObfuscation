# CMake Cache Fix Instructions

## Problem
The CMake cache is pointing to a different directory (`/home/mitva/advanced-llvm-obfuscator/build`) than your current project directory (`/home/mohini/LLVMObfuscation/build`).

## Solution
Run these commands in your WSL terminal:

### Step 1: Clean the build directory
```bash
cd /home/mohini/LLVMObfuscation
rm -rf build
mkdir build
```

### Step 2: Configure CMake
```bash
cmake -B build -S . -DCMAKE_BUILD_TYPE=Release
```

### Step 3: Build the project
```bash
cmake --build build
```

### Alternative: Use the build script
```bash
./build_sih.sh
```

## What this fixes
- Removes the old CMake cache that was pointing to the wrong directory
- Creates a fresh build directory
- Configures CMake with the correct source directory
- Builds the project successfully

## Files created
- `fix_cmake.sh` - Shell script to automate the fix
- `fix_cmake.bat` - Windows batch file alternative
- `fix_cmake.ps1` - PowerShell script alternative

## Manual execution
If the automated scripts don't work, you can run the commands manually in your WSL terminal.
