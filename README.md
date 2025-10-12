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
