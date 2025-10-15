#!/bin/bash
# ========================================
# SIH Quick Setup Script
# For SIH hackathon - minimal setup
# ========================================

set -e

echo "🚀 SIH LLVM Obfuscator - Quick Setup"
echo "====================================="

# Check if we're in WSL/Linux
if [[ "$OSTYPE" == "linux-gnu"* ]]; then
    echo "✅ Linux environment detected"
else
    echo "❌ This script requires Linux/WSL environment"
    echo "Please run this in WSL terminal, not PowerShell"
    exit 1
fi

# Install LLVM and dependencies
echo "📦 Installing LLVM and dependencies..."
sudo apt update
sudo apt install -y llvm-dev clang cmake build-essential

# Verify installation
echo "🔍 Verifying installation..."
if command -v llvm-config &> /dev/null; then
    echo "✅ LLVM found: $(llvm-config --version)"
else
    echo "❌ LLVM installation failed"
    exit 1
fi

if command -v clang &> /dev/null; then
    echo "✅ Clang found: $(clang --version | head -n1)"
else
    echo "❌ Clang installation failed"
    exit 1
fi

# Build the project
echo "🔨 Building SIH obfuscator..."
mkdir -p build
cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Build
make -j$(nproc 2>/dev/null || echo 4)

echo "✅ Build completed!"

# Create test file if it doesn't exist
cd ..
if [ ! -f test/sih_demo.c ]; then
    echo "📝 Creating SIH demo file..."
    mkdir -p test
    cat > test/sih_demo.c << 'EOF'
#include <stdio.h>
#include <string.h>

int authenticate(char* user, char* pass) {
    return strcmp(user, "admin") == 0 && strcmp(pass, "admin123") == 0;
}

int main(int argc, char* argv[]) {
    printf("=== SIH LLVM Obfuscator Demo ===\n");
    
    if (argc < 3) {
        printf("Usage: %s <user> <pass>\n", argv[0]);
        return 1;
    }
    
    if (authenticate(argv[1], argv[2])) {
        printf("✅ Access granted!\n");
        printf("🔐 Secret: SIH2024\n");
    } else {
        printf("❌ Access denied!\n");
    }
    
    return 0;
}
EOF
fi

# Test the build
echo "🧪 Testing SIH obfuscator..."
if [ -f "build/sih-obfuscator" ]; then
    echo "✅ SIH obfuscator built successfully"
    echo ""
    echo "🎯 Ready for SIH demo!"
    echo ""
    echo "📋 Next steps:"
    echo "1. Run: ./build/sih-obfuscator test/sih_demo.c"
    echo "2. Follow interactive prompts"
    echo "3. Test obfuscated binary"
    echo "4. Show generated report"
    echo ""
    echo "🚀 Good luck with your SIH presentation!"
else
    echo "❌ SIH obfuscator build failed"
    echo "Check the error messages above"
    exit 1
fi
