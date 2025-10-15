#!/bin/bash
# ========================================
# SIH LLVM Obfuscator Build Script
# Enhanced for cross-platform support
# ========================================

set -e

echo "🔧 SIH LLVM Obfuscator Build Script"
echo "===================================="

# Detect platform
PLATFORM=$(uname -s)
ARCH=$(uname -m)

echo "🖥️  Platform: $PLATFORM"
echo "🏗️  Architecture: $ARCH"

# Check if LLVM is available
if ! command -v llvm-config &> /dev/null; then
    echo "❌ LLVM not found. Please install LLVM development tools."
    echo "   Ubuntu/Debian: sudo apt install llvm-dev clang"
    echo "   CentOS/RHEL: sudo yum install llvm-devel clang"
    echo "   Windows: Install LLVM from https://releases.llvm.org/"
    exit 1
fi

LLVM_VERSION=$(llvm-config --version | cut -d. -f1)
echo "✅ Found LLVM version: $LLVM_VERSION"

# Create project structure
echo "📁 Creating project structure..."
mkdir -p build passes src reports test

# Build the project
echo "🔨 Building LLVM passes and SIH application..."
cd build

# Configure with CMake for cross-platform support
CMAKE_FLAGS="-DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON"

# Platform-specific configurations
if [[ "$PLATFORM" == "Linux" ]]; then
    echo "🐧 Configuring for Linux..."
    CMAKE_FLAGS="$CMAKE_FLAGS -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++"
elif [[ "$PLATFORM" == "Darwin" ]]; then
    echo "🍎 Configuring for macOS..."
    CMAKE_FLAGS="$CMAKE_FLAGS -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++"
elif [[ "$PLATFORM" == "MINGW"* ]] || [[ "$PLATFORM" == "CYGWIN"* ]]; then
    echo "🪟 Configuring for Windows..."
    CMAKE_FLAGS="$CMAKE_FLAGS -DCMAKE_C_COMPILER=clang -DCMAKE_CXX_COMPILER=clang++"
fi

cmake .. $CMAKE_FLAGS

# Build all targets
echo "🔨 Building targets..."
make -j$(nproc 2>/dev/null || echo 4) || make -j1

echo "✅ Build completed successfully!"

# Test the installation
echo "🧪 Testing SIH obfuscator..."
cd ..

# Create SIH test files if they don't exist
if [ ! -f test/sih_demo.c ]; then
    cat > test/sih_demo.c << 'EOF'
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Authentication function for SIH demo
int authenticate_user(char* username, char* password) {
    char* valid_users[] = {"admin", "user", "guest"};
    char* valid_passwords[] = {"admin123", "userpass", "guest"};
    
    for (int i = 0; i < 3; i++) {
        if (strcmp(username, valid_users[i]) == 0 && 
            strcmp(password, valid_passwords[i]) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

// Secret algorithm for SIH demo
int calculate_secret_value(int input) {
    int result = input;
    
    // Complex computation
    for (int i = 0; i < 10; i++) {
        if (result % 2 == 0) {
            result = result / 2;
        } else {
            result = result * 3 + 1;
        }
    }
    
    return result;
}

int main(int argc, char* argv[]) {
    printf("=== SIH LLVM Obfuscator Demo ===\n");
    
    if (argc < 3) {
        printf("Usage: %s <username> <password>\n", argv[0]);
        return 1;
    }
    
    char* username = argv[1];
    char* password = argv[2];
    
    printf("Authenticating user: %s\n", username);
    
    if (authenticate_user(username, password)) {
        printf("✅ Authentication successful!\n");
        
        int secret_value = calculate_secret_value(42);
        printf("🔐 Secret value: %d\n", secret_value);
        
        printf("🎉 Access granted to secure system!\n");
    } else {
        printf("❌ Authentication failed!\n");
        printf("🚫 Access denied!\n");
    }
    
    return 0;
}
EOF
fi

# Test SIH obfuscator
echo "🚀 Testing SIH obfuscator..."
if [ -f build/sih-obfuscator ]; then
    echo "✅ SIH obfuscator built successfully"
    echo "📋 Usage example:"
    echo "./build/sih-obfuscator test/sih_demo.c"
else
    echo "❌ SIH obfuscator not found"
    exit 1
fi

# Create Windows batch file for cross-platform support
cat > build_sih.bat << 'EOF'
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
EOF

echo ""
echo "🎉 SIH Build completed successfully!"
echo ""
echo "📖 Quick Start Guide:"
echo "===================="
echo "1. Run SIH obfuscator:"
echo "   ./build/sih-obfuscator test/sih_demo.c"
echo ""
echo "2. For Windows users:"
echo "   build_sih.bat"
echo ""
echo "3. Check results:"
echo "   - Obfuscated binary: ./obfuscated_binary"
echo "   - Report: ./reports/sih_obfuscation_report.txt"
echo "   - HTML Report: ./reports/sih_obfuscation_report.txt.html"
echo ""
echo "4. Demo workflow:"
echo "   ./build/sih-obfuscator test/sih_demo.c"
echo "   ./obfuscated_binary admin admin123"
echo ""
echo "🔒 Ready for SIH presentation!"
