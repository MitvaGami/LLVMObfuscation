# 🚀 SIH LLVM Obfuscator - Setup Guide

## 📋 **Quick Setup for SIH Hackathon**

### **Step 1: Install LLVM and Dependencies**

Open your **WSL terminal** (not PowerShell) and run:

```bash
# Update package list
sudo apt update

# Install LLVM development tools
sudo apt install -y llvm-dev clang cmake build-essential

# Verify installation
llvm-config --version
clang --version
```

### **Step 2: Build the SIH Obfuscator**

```bash
# Navigate to your project directory
cd /home/mohini/LLVMObfuscation

# Make build script executable
chmod +x build_sih.sh

# Run the build script
./build_sih.sh
```

### **Step 3: Test the Installation**

```bash
# Run the test script
chmod +x test_sih.sh
./test_sih.sh
```

### **Step 4: Run SIH Demo**

```bash
# Run the interactive SIH obfuscator
./build/sih-obfuscator test/sih_demo.c
```

## 🎯 **Alternative Setup (If LLVM Installation Fails)**

### **Option 1: Use Docker (Recommended for SIH)**

Create a `Dockerfile`:

```dockerfile
FROM ubuntu:20.04

# Install dependencies
RUN apt-get update && apt-get install -y \
    llvm-dev \
    clang \
    cmake \
    build-essential \
    git

# Set working directory
WORKDIR /app

# Copy project files
COPY . .

# Build the project
RUN chmod +x build_sih.sh && ./build_sih.sh

# Default command
CMD ["./build/sih-obfuscator", "test/sih_demo.c"]
```

Build and run:
```bash
docker build -t sih-obfuscator .
docker run -it sih-obfuscator
```

### **Option 2: Use Pre-built LLVM**

```bash
# Download LLVM pre-built binaries
wget https://github.com/llvm/llvm-project/releases/download/llvmorg-15.0.0/clang+llvm-15.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz

# Extract
tar -xf clang+llvm-15.0.0-x86_64-linux-gnu-ubuntu-18.04.tar.xz

# Add to PATH
export PATH=$PWD/clang+llvm-15.0.0-x86_64-linux-gnu-ubuntu-18.04/bin:$PATH

# Verify
llvm-config --version
```

## 🚀 **Quick Demo for SIH Presentation**

### **Minimal Demo Setup**

If you're short on time, here's a minimal demo:

```bash
# 1. Install minimal LLVM
sudo apt install -y llvm-12-dev clang-12

# 2. Build only the essential components
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4

# 3. Create a simple test
cat > ../test_simple.c << 'EOF'
#include <stdio.h>
int main() {
    printf("Hello SIH!\n");
    return 0;
}
EOF

# 4. Run obfuscation
./sih-obfuscator ../test_simple.c
```

## 🎯 **SIH Presentation Script**

### **Opening (30 seconds)**
"Good morning judges. We present our SIH solution: an LLVM-based obfuscation tool with interactive configuration, cross-platform support, and comprehensive reporting."

### **Live Demo (10 minutes)**
1. **Show original code** (1 min)
2. **Run interactive obfuscator** (5 mins)
3. **Show obfuscated binary** (2 mins)
4. **Display report** (2 mins)

### **Key Points to Highlight**
- ✅ **Interactive Configuration**: Platform, performance, cycles, techniques
- ✅ **Cross-Platform**: Windows/Linux binary generation
- ✅ **SIH Compliance**: All required metrics in report
- ✅ **Security**: High reverse engineering difficulty
- ✅ **Functionality**: Obfuscated binary works identically

## 🛠️ **Troubleshooting**

### **Common Issues:**

1. **LLVM not found:**
```bash
# Try different LLVM versions
sudo apt install -y llvm-12-dev llvm-13-dev llvm-14-dev
```

2. **Build fails:**
```bash
# Clean and rebuild
rm -rf build/
mkdir build && cd build
cmake .. -DCMAKE_BUILD_TYPE=Release
make -j4
```

3. **Passes not loading:**
```bash
# Check if .so files exist
ls -la build/*.so
```

4. **Permission denied:**
```bash
chmod +x build_sih.sh test_sih.sh
```

## 🎉 **Success Criteria**

Your SIH demo is successful if:
- ✅ Interactive configuration works
- ✅ Obfuscation completes without errors
- ✅ Obfuscated binary runs correctly
- ✅ Report shows all SIH metrics
- ✅ Cross-platform targeting works

## 📞 **Emergency Setup (5 minutes)**

If you're running out of time:

```bash
# Quick LLVM install
sudo apt install -y llvm-dev clang

# Quick build
mkdir build && cd build
cmake .. && make -j4

# Quick demo
./sih-obfuscator ../test/sih_demo.c
```

**Good luck with your SIH presentation! 🚀**
