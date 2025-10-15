# 🚀 SIH LLVM Obfuscator - Demo Guide

## 📋 **Pre-Demo Setup (5 minutes)**

### 1. Build the Project
```bash
# Make build script executable
chmod +x build_sih.sh

# Run the build script
./build_sih.sh
```

### 2. Verify Installation
```bash
# Check if SIH obfuscator is built
ls -la build/sih-obfuscator

# Check if all passes are available
ls -la build/*.so
```

## 🎯 **Demo Workflow (15 minutes)**

### **Phase 1: Show Original Code (2 minutes)**

1. **Display the source code:**
```bash
cat test/sih_demo.c
```

2. **Compile and run original:**
```bash
gcc test/sih_demo.c -o original_demo
./original_demo admin admin123
```

**Expected Output:**
```
=== SIH LLVM Obfuscator Demo ===
Authenticating user: admin
✅ Authentication successful!
🔐 Secret value: 1
🎉 Access granted to secure system!
```

### **Phase 2: Interactive Obfuscation (8 minutes)**

1. **Run SIH obfuscator with interactive mode:**
```bash
./build/sih-obfuscator test/sih_demo.c
```

2. **Follow the interactive prompts:**

**Platform Selection:**
```
🖥️  PLATFORM & TARGET CONFIGURATION
=====================================
Select target platform:
1. Linux
2. Windows
Choice (1-2): 1

Select target architecture:
1. x86 (32-bit)
2. x64 (64-bit)
3. ARM
Choice (1-3): 2
```

**Performance Settings:**
```
⚡ PERFORMANCE & SIZE BUDGET
============================
Maximum allowed size increase (%): 500
Maximum allowed runtime overhead (%): 30
Enforce limits strictly? (y/n): n
```

**Obfuscation Cycles:**
```
🔄 OBFUSCATION CYCLES
=====================
Number of obfuscation cycles (1-10): 3
```

**Technique Selection:**
```
🔧 OBFUSCATION TECHNIQUES
=========================
1. Control Flow Flattening
   Enable? (y/n): y
   Intensity (1-5): 4
   Aggressiveness (0.0-1.0): 0.8

2. Bogus Control Flow
   Enable? (y/n): y
   Intensity (1-5): 3
   Aggressiveness (0.0-1.0): 0.6

3. String Encryption
   Enable? (y/n): y
   Intensity (1-5): 5
   Aggressiveness (0.0-1.0): 0.9

4. Instruction Substitution
   Enable? (y/n): y
   Intensity (1-5): 3
   Aggressiveness (0.0-1.0): 0.5

5. Opaque Predicates
   Enable? (y/n): y
   Intensity (1-5): 4
   Aggressiveness (0.0-1.0): 0.7

6. Function Splitting
   Enable? (y/n): n

7. Symbol Stripping
   Enable? (y/n): y
   Intensity (1-5): 5
   Aggressiveness (0.0-1.0): 1.0

8. Anti-Disassembly
   Enable? (y/n): y
   Intensity (1-5): 3
   Aggressiveness (0.0-1.0): 0.6
```

### **Phase 3: Show Obfuscation Process (3 minutes)**

**Watch the obfuscation process:**
```
🚀 STARTING OBFUSCATION PROCESS
================================

🔄 GENERATING LLVM IR
=====================
Command: clang -S -emit-llvm -target x64-pc-linux-gnu "test/sih_demo.c" -o input.ll 2>/dev/null

🔒 APPLYING OBFUSCATION PASSES
===============================

--- Cycle 1/3 ---
  ✓ cf-flatten applied (cycle 1)
  ✓ advanced-bogus applied (cycle 1)
  ✓ poly-string applied (cycle 1)
  ✓ opaque-pred applied (cycle 1)
  ✓ func-split applied (cycle 1)

--- Cycle 2/3 ---
  ✓ cf-flatten applied (cycle 2)
  ✓ advanced-bogus applied (cycle 2)
  ✓ poly-string applied (cycle 2)
  ✓ opaque-pred applied (cycle 2)

--- Cycle 3/3 ---
  ✓ cf-flatten applied (cycle 3)
  ✓ advanced-bogus applied (cycle 3)
  ✓ poly-string applied (cycle 3)
  ✓ opaque-pred applied (cycle 3)

🔨 COMPILING TO BINARY
=====================
Command: clang obfuscated.ll -o obfuscated_binary 2>/dev/null
✓ Binary generated: obfuscated_binary
```

### **Phase 4: Demonstrate Results (2 minutes)**

1. **Run obfuscated binary:**
```bash
./obfuscated_binary admin admin123
```

**Expected Output (same functionality):**
```
=== SIH LLVM Obfuscator Demo ===
Authenticating user: admin
✅ Authentication successful!
🔐 Secret value: 1
🎉 Access granted to secure system!
```

2. **Show the SIH report:**
```bash
cat reports/sih_obfuscation_report.txt
```

3. **Open HTML report:**
```bash
# On Linux
xdg-open reports/sih_obfuscation_report.txt.html

# On Windows
start reports/sih_obfuscation_report.txt.html
```

## 📊 **Key Demo Points to Highlight**

### **1. Interactive Configuration**
- ✅ Platform selection (Windows/Linux)
- ✅ Architecture targeting (x86/x64/ARM)
- ✅ Performance budget controls
- ✅ Technique selection with intensity/aggressiveness
- ✅ Multiple obfuscation cycles

### **2. SIH Requirements Compliance**
- ✅ **Input Parameters Logged**: All user inputs captured
- ✅ **Output File Attributes**: Size, platform, methods logged
- ✅ **Bogus Code Generated**: Detailed count and metrics
- ✅ **Obfuscation Cycles**: Number of cycles completed
- ✅ **String Encryption**: Count of encrypted strings
- ✅ **Fake Loops**: Number of fake loops inserted

### **3. Cross-Platform Support**
- ✅ **Linux**: Native ELF binary generation
- ✅ **Windows**: PE binary generation with proper targeting
- ✅ **Architecture Support**: x86, x64, ARM targeting

### **4. Advanced Features**
- ✅ **Multiple Obfuscation Techniques**: 8 different methods
- ✅ **Configurable Intensity**: 1-5 scale per technique
- ✅ **Aggressiveness Control**: 0.0-1.0 scale
- ✅ **Performance Monitoring**: Size and runtime overhead tracking
- ✅ **Security Assessment**: Reverse engineering difficulty scoring

## 🎯 **Presentation Script**

### **Opening (1 minute)**
"Good morning/afternoon judges. We present our solution for the SIH problem statement on LLVM-based object file obfuscation. Our tool provides comprehensive obfuscation with interactive configuration, cross-platform support, and detailed reporting as required."

### **Problem Statement Alignment (2 minutes)**
"Our solution addresses all SIH requirements:
- Interactive parameter collection for platform, performance, and technique selection
- Cross-platform binary generation for Windows and Linux
- Comprehensive reporting with all required metrics
- Multiple obfuscation techniques with configurable intensity"

### **Live Demo (10 minutes)**
"Let me demonstrate our tool in action..."

### **Results Analysis (2 minutes)**
"As you can see from the report:
- We successfully obfuscated the binary while maintaining functionality
- All input parameters are logged as required
- Output file attributes are captured
- Bogus code generation is tracked
- String encryption and fake loop insertion are measured
- Security assessment shows high reverse engineering difficulty"

### **Closing (1 minute)**
"Our SIH LLVM Obfuscator provides a complete solution for intellectual property protection with user-friendly configuration, comprehensive reporting, and cross-platform support. Thank you for your attention."

## 🛠️ **Troubleshooting**

### **Common Issues:**

1. **LLVM not found:**
```bash
sudo apt install llvm-dev clang
```

2. **Build fails:**
```bash
# Clean and rebuild
rm -rf build/
./build_sih.sh
```

3. **Passes not loading:**
```bash
# Check if .so files exist
ls -la build/*.so
```

4. **Binary not executable:**
```bash
chmod +x obfuscated_binary
```

## 📈 **Success Metrics**

- ✅ **Functionality Preserved**: Obfuscated binary works identically to original
- ✅ **SIH Requirements Met**: All problem statement requirements addressed
- ✅ **Cross-Platform**: Works on both Windows and Linux
- ✅ **Interactive**: User-friendly configuration process
- ✅ **Comprehensive Reporting**: Detailed metrics and analysis
- ✅ **Security**: High reverse engineering difficulty

## 🎉 **Demo Success Criteria**

Your demo is successful if:
- ✅ Interactive configuration works smoothly
- ✅ Obfuscation process completes without errors
- ✅ Obfuscated binary runs and produces correct output
- ✅ Report generation works and shows all required metrics
- ✅ HTML dashboard displays properly
- ✅ Cross-platform targeting works
- ✅ All SIH requirements are demonstrated

**Good luck with your SIH presentation! 🚀**
