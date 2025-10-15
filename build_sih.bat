@echo off
echo 🔧 SIH LLVM Obfuscator Build Script (Windows)
echo =============================================

REM Check if LLVM is available
where llvm-config >nul 2>nul
if %ERRORLEVEL% neq 0 (
    echo ❌ LLVM not found. Please install LLVM development tools.
    echo    Download from: https://releases.llvm.org/
    pause
    exit /b 1
)

echo ✅ LLVM found

REM Create build directory
if not exist build mkdir build
cd build

REM Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

REM Build
cmake --build . --config Release

echo ✅ Build completed successfully!
echo.
echo 🚀 SIH Obfuscator Usage:
echo    sih-obfuscator.exe your_file.c
echo.
pause
