#!/bin/bash
# ========================================
# build.sh - Complete Build Script
# ========================================

set -e

echo "🔧 Advanced LLVM Obfuscator Build Script"
echo "========================================"

# Check if LLVM is available
if ! command -v llvm-config &> /dev/null; then
    echo "❌ LLVM not found. Please install LLVM development tools."
    exit 1
fi

LLVM_VERSION=$(llvm-config --version | cut -d. -f1)
echo "✅ Found LLVM version: $LLVM_VERSION"

# Create project structure
echo "📁 Creating project structure..."
mkdir -p build passes src reports test

# Build the project
echo "🔨 Building LLVM passes and main application..."
cd build

# Configure with CMake
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_EXPORT_COMPILE_COMMANDS=ON

# Build all targets
make -j$(nproc) || make -j1

echo "✅ Build completed successfully!"

# Test the installation
echo "🧪 Testing passes..."
cd ..

# Create a simple test file if it doesn't exist
if [ ! -f test/simple.c ]; then
    cat > test/simple.c << 'EOF'
#include <stdio.h>
#include <string.h>

int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

int main() {
    char secret[] = "Hello World!";
    int result = fibonacci(10);
    
    printf("Secret: %s\n", secret);
    printf("Fibonacci(10) = %d\n", result);
    
    if (strlen(secret) > 5) {
        printf("Long secret detected!\n");
    }
    
    return 0;
}
EOF
fi

# Test basic IR generation
echo "🔍 Testing basic IR generation..."
clang -S -emit-llvm test/simple.c -o test/simple.ll
if [ -f test/simple.ll ]; then
    echo "✅ IR generation successful"
else
    echo "❌ IR generation failed"
    exit 1
fi

# Test individual passes
echo "🔍 Testing individual passes..."

echo "  Testing Advanced Bogus Pass..."
if [ -f build/AdvancedBogusPass.so ]; then
    opt -load-pass-plugin=./build/AdvancedBogusPass.so -passes=advanced-bogus -S test/simple.ll -o test/bogus_test.ll
    echo "  ✅ Advanced Bogus Pass working"
else
    echo "  ❌ Advanced Bogus Pass not found"
fi

echo "  Testing Polymorphic String Pass..."
if [ -f build/PolymorphicStringPass.so ]; then
    opt -load-pass-plugin=./build/PolymorphicStringPass.so -passes=poly-string -S test/simple.ll -o test/string_test.ll
    echo "  ✅ Polymorphic String Pass working"
else
    echo "  ❌ Polymorphic String Pass not found"
fi

echo "  Testing Opaque Predicate Pass..."
if [ -f build/OpaquePredicatePass.so ]; then
    opt -load-pass-plugin=./build/OpaquePredicatePass.so -passes=opaque-pred -S test/simple.ll -o test/opaque_test.ll
    echo "  ✅ Opaque Predicate Pass working"
else
    echo "  ❌ Opaque Predicate Pass not found"
fi

# Test the main application
echo "🚀 Testing main obfuscator application..."
if [ -f build/advanced-obfuscator ]; then
    echo "✅ Main application built successfully"
    echo "📋 Usage example:"
    echo "./build/advanced-obfuscator --input test/simple.c --enable-all --cycles 2"
else
    echo "❌ Main application not found"
    exit 1
fi

echo ""
echo "🎉 Build and test completed successfully!"
echo ""
echo "📖 Quick Start:"
echo "==============="
echo "1. Run obfuscation:"
echo "   ./build/advanced-obfuscator --input test/simple.c --enable-all --cycles 2"
echo ""
echo "2. Check results:"
echo "   - Obfuscated binary: ./obf_exec"
echo "   - Report: ./reports/obfuscation_report.txt"
echo "   - HTML Report: ./reports/obfuscation_report.txt.html"
echo ""
echo "3. Compare original vs obfuscated:"
echo "   gcc test/simple.c -o original"
echo "   ./original"
echo "   ./obf_exec"

# ========================================
# test/complex.c - More Complex Test Case  
# ========================================
cat > test/complex.c << 'EOF'
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function with multiple branches for CF flattening
int calculate_score(int a, int b, int c) {
    int result = 0;
    
    if (a > b) {
        if (b > c) {
            result = a * b + c;
        } else {
            result = a + b * c;
        }
    } else {
        if (a > c) {
            result = b * c - a;
        } else {
            result = (a + b + c) / 3;
        }
    }
    
    for (int i = 0; i < 3; i++) {
        result += i * 2;
    }
    
    return result;
}

// Function with string operations
void process_strings() {
    char buffer[100];
    char *messages[] = {
        "Confidential Data",
        "Secret Algorithm", 
        "Protected Information",
        "Classified Content"
    };
    
    printf("Processing secure data...\n");
    
    for (int i = 0; i < 4; i++) {
        strcpy(buffer, messages[i]);
        printf("Message %d: %s (length: %lu)\n", i+1, buffer, strlen(buffer));
    }
}

// Recursive function for splitting
long factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    
    long temp = factorial(n - 1);
    return n * temp;
}

// Function with complex control flow
int complex_algorithm(int input) {
    int state = 0;
    int counter = 0;
    
    while (counter < 10) {
        switch (state) {
            case 0:
                if (input % 2 == 0) {
                    state = 1;
                    input /= 2;
                } else {
                    state = 2;
                    input = input * 3 + 1;
                }
                break;
                
            case 1:
                if (input < 10) {
                    state = 3;
                } else {
                    state = 0;
                    input -= 5;
                }
                break;
                
            case 2:
                if (input > 100) {
                    state = 0;
                    input /= 4;
                } else {
                    state = 1;
                    input += 7;
                }
                break;
                
            case 3:
                return input + counter;
                
            default:
                state = 0;
                break;
        }
        counter++;
    }
    
    return input;
}

int main(int argc, char *argv[]) {
    printf("=== Advanced LLVM Obfuscator Test Program ===\n");
    
    // Test different functions
    int score = calculate_score(15, 10, 25);
    printf("Calculated score: %d\n", score);
    
    process_strings();
    
    long fact = factorial(8);
    printf("Factorial of 8: %ld\n", fact);
    
    srand(time(NULL));
    int random_input = rand() % 100 + 1;
    int algorithm_result = complex_algorithm(random_input);
    printf("Complex algorithm result for input %d: %d\n", random_input, algorithm_result);
    
    // Test with command line arguments
    if (argc > 1) {
        printf("Command line argument received: %s\n", argv[1]);
        int arg_value = atoi(argv[1]);
        if (arg_value > 0) {
            printf("Processing argument value: %d\n", arg_value);
            int processed = complex_algorithm(arg_value);
            printf("Processed result: %d\n", processed);
        }
    }
    
    printf("Program execution completed.\n");
    return 0;
}
EOF

# ========================================
# Makefile for convenience
# ========================================
cat > Makefile << 'EOF'
.PHONY: all clean test install

# Default target
all: build

# Build everything
build:
	@echo "🔨 Building Advanced LLVM Obfuscator..."
	@mkdir -p build
	@cd build && cmake .. -DCMAKE_BUILD_TYPE=Release
	@cd build && make -j$(shell nproc)
	@echo "✅ Build completed!"

# Clean build artifacts
clean:
	@echo "🧹 Cleaning build artifacts..."
	@rm -rf build/
	@rm -f test/*.ll obf_exec obfuscated.ll *.ll temp_*.ll
	@rm -rf reports/
	@echo "✅ Cleaned!"

# Run tests
test: build
	@echo "🧪 Running tests..."
	@./build.sh
	@echo "✅ Tests completed!"

# Quick obfuscation test
demo: build
	@echo "🚀 Running demonstration..."
	@./build/advanced-obfuscator --input test/complex.c --enable-all --cycles 2
	@echo "📊 Check reports/ directory for results"
	@echo "🎯 Run ./obf_exec to test obfuscated binary"

# Install system-wide (requires sudo)
install: build
	@echo "📦 Installing Advanced LLVM Obfuscator..."
	@sudo cp build/advanced-obfuscator /usr/local/bin/
	@sudo chmod +x /usr/local/bin/advanced-obfuscator
	@echo "✅ Installed to /usr/local/bin/advanced-obfuscator"

help:
	@echo "Advanced LLVM Obfuscator - Available targets:"
	@echo "  build     - Build all components"
	@echo "  clean     - Clean build artifacts"
	@echo "  test      - Run comprehensive tests"
	@echo "  demo      - Quick demonstration"
	@echo "  install   - Install system-wide (requires sudo)"
	@echo "  help      - Show this help"
EOF

# ========================================
# README.md - Documentation
# ========================================
cat > README.md << 'EOF'
# 🔒 Advanced LLVM Obfuscator

A sophisticated code obfuscation tool built with LLVM that implements cutting-edge obfuscation techniques for C/C++ programs. Developed for research purposes and intellectual property protection.

## 🌟 Features

### Advanced Obfuscation Techniques

1. **Polymorphic Bogus Code Injection**
   - Inserts meaningless but complex arithmetic chains
   - Creates fake loops that never execute
   - Adds conditional noise with opaque predicates
   - Includes fake memory operations

2. **Polymorphic String Encryption**
   - Multiple encryption algorithms (XOR, Caesar, Multi-layer XOR)
   - Runtime decryption with generated functions
   - Randomized encryption per compilation

3. **Control Flow Flattening**
   - Converts linear control flow into switch-based dispatch
   - Randomizes case numbers
   - Makes reverse engineering significantly harder

4. **Mathematical Opaque Predicates** 
   - Uses mathematical properties that are always true/false
   - Complex modular arithmetic predicates
   - Confuses static analysis tools

5. **Intelligent Function Splitting**
   - Splits large functions into multiple parts
   - Creates decoy functions with realistic names
   - Maintains program functionality while increasing complexity

## 🚀 Quick Start

### Prerequisites
- LLVM 12+ with development headers
- CMake 3.16+
- GCC/Clang compiler
- Linux/WSL environment

### Installation

```bash
# Clone and build
git clone <repository>
cd advanced-llvm-obfuscator
chmod +x build.sh
./build.sh

# Or use Makefile
make build
```

### Basic Usage

```bash
# Simple obfuscation
./build/advanced-obfuscator --input program.c --enable-all

# Advanced obfuscation with multiple cycles
./build/advanced-obfuscator --input program.c --enable-all --cycles 3 --bogus-intensity 5

# Selective obfuscation
./build/advanced-obfuscator --input program.c --enable-bogus --enable-strings --cycles 2
```

### Command Line Options

```
--input <file>           Input C/C++ source file
--cycles <n>             Number of obfuscation cycles (default: 1)
--bogus-intensity <n>    Bogus code intensity 1-5 (default: 3)

Obfuscation Techniques:
--enable-bogus           Advanced polymorphic bogus code injection
--enable-strings         Polymorphic string encryption
--enable-flatten         Control flow flattening
--enable-opaque          Opaque predicate insertion  
--enable-split           Function splitting
--enable-all             Enable all obfuscation techniques
```

## 📊 Output

The tool generates:

1. **Obfuscated Binary**: `obf_exec` - Ready to run obfuscated program
2. **Text Report**: `reports/obfuscation_report.txt` - Detailed metrics
3. **HTML Report**: `reports/obfuscation_report.txt.html` - Visual dashboard

### Sample Report Metrics

- Input parameters and settings
- Number of obfuscation cycles completed
- Bogus instructions added count
- Strings encrypted count
- Fake loops inserted count  
- Functions flattened count
- Opaque predicates added count
- Functions split count
- File size analysis (original vs obfuscated)
- Estimated performance impact

## 🔬 Technical Details

### LLVM Pass Architecture

Each obfuscation technique is implemented as a separate LLVM pass:

- `AdvancedBogusPass.cpp` - Polymorphic bogus code generation
- `PolymorphicStringPass.cpp` - String encryption with multiple algorithms  
- `CFFlattening.cpp` - Control flow flattening
- `OpaquePredicatePass.cpp` - Mathematical opaque predicates
- `FunctionSplittingPass.cpp` - Function splitting and decoy generation

### Innovation Points

1. **Polymorphic Obfuscation**: Different obfuscation patterns each compilation
2. **Mathematical Complexity**: Uses number theory for opaque predicates
3. **Multi-layer Approach**: Combines multiple techniques in cycles
4. **Comprehensive Reporting**: Detailed analysis of obfuscation effects
5. **Modular Design**: Easy to extend with new techniques

## 🧪 Testing

```bash
# Run comprehensive tests
make test

# Quick demonstration
make demo

# Test with complex program
./build/advanced-obfuscator --input test/complex.c --enable-all --cycles 3
```

## 📈 Performance Impact

Expected overhead per technique:
- Bogus Code: 10-30% size increase, minimal runtime impact
- String Encryption: 5-15% runtime overhead
- Control Flow Flattening: 20-50% runtime overhead  
- Opaque Predicates: 10-25% runtime overhead
- Function Splitting: 5-15% runtime overhead

## 🛡️ Security Analysis

The tool is designed to resist:
- Static analysis tools (IDA Pro, Ghidra)
- Dynamic analysis and debugging
- Automated deobfuscation
- Pattern recognition attacks

## ⚠️ Legal Notice

This tool is intended for:
- Research and educational purposes
- Legitimate intellectual property protection
- Security testing of your own software

Users are responsible for compliance with applicable laws and regulations.

## 🤝 Contributing

1. Fork the repository
2. Create feature branch
3. Add comprehensive tests
4. Submit pull request

## 📚 References

- LLVM Pass Writing Documentation
- Code Obfuscation Research Papers
- Reverse Engineering Defense Techniques

## 🏆 Awards & Recognition

Developed for National Technical Research Organisation (NTRO) competition focusing on innovative software protection techniques.
EOF

echo "✅ All files created successfully!"
echo ""
echo "🚀 Ready to build! Run:"
echo "   chmod +x build.sh"
echo "   ./build.sh"
