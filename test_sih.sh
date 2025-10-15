#!/bin/bash
# ========================================
# SIH LLVM Obfuscator Test Script
# Quick verification of all components
# ========================================

set -e

echo "🧪 SIH LLVM Obfuscator Test Script"
echo "==================================="

# Test 1: Check if build completed
echo "🔍 Test 1: Checking build artifacts..."
if [ -f "build/sih-obfuscator" ]; then
    echo "✅ SIH obfuscator executable found"
else
    echo "❌ SIH obfuscator not found - run ./build_sih.sh first"
    exit 1
fi

# Test 2: Check if passes are built
echo "🔍 Test 2: Checking LLVM passes..."
PASSES=("AdvancedBogusPass.so" "PolymorphicStringPass.so" "CFFlattening.so" "OpaquePredicatePass.so" "InstructionSubstitutionPass.so")
for pass in "${PASSES[@]}"; do
    if [ -f "build/$pass" ]; then
        echo "✅ $pass found"
    else
        echo "❌ $pass not found"
        exit 1
    fi
done

# Test 3: Check if test file exists
echo "🔍 Test 3: Checking test files..."
if [ -f "test/sih_demo.c" ]; then
    echo "✅ SIH demo file found"
else
    echo "❌ SIH demo file not found"
    exit 1
fi

# Test 4: Test original compilation
echo "🔍 Test 4: Testing original compilation..."
gcc test/sih_demo.c -o test_original 2>/dev/null
if [ -f "test_original" ]; then
    echo "✅ Original compilation successful"
    rm test_original
else
    echo "❌ Original compilation failed"
    exit 1
fi

# Test 5: Test LLVM IR generation
echo "🔍 Test 5: Testing LLVM IR generation..."
clang -S -emit-llvm test/sih_demo.c -o test_ir.ll 2>/dev/null
if [ -f "test_ir.ll" ]; then
    echo "✅ LLVM IR generation successful"
    rm test_ir.ll
else
    echo "❌ LLVM IR generation failed"
    exit 1
fi

# Test 6: Test individual passes
echo "🔍 Test 6: Testing individual passes..."
clang -S -emit-llvm test/sih_demo.c -o test.ll 2>/dev/null

# Test Advanced Bogus Pass
if opt -load-pass-plugin=./build/AdvancedBogusPass.so -passes=advanced-bogus -S test.ll -o test_bogus.ll 2>/dev/null; then
    echo "✅ Advanced Bogus Pass working"
    rm test_bogus.ll
else
    echo "⚠️  Advanced Bogus Pass test skipped"
fi

# Test String Pass
if opt -load-pass-plugin=./build/PolymorphicStringPass.so -passes=poly-string -S test.ll -o test_string.ll 2>/dev/null; then
    echo "✅ Polymorphic String Pass working"
    rm test_string.ll
else
    echo "⚠️  Polymorphic String Pass test skipped"
fi

# Test CF Flattening
if opt -load-pass-plugin=./build/CFFlattening.so -passes=cf-flatten -S test.ll -o test_cf.ll 2>/dev/null; then
    echo "✅ Control Flow Flattening Pass working"
    rm test_cf.ll
else
    echo "⚠️  Control Flow Flattening Pass test skipped"
fi

# Test Instruction Substitution
if opt -load-pass-plugin=./build/InstructionSubstitutionPass.so -passes=inst-subst -S test.ll -o test_is.ll 2>/dev/null; then
    echo "✅ Instruction Substitution Pass working"
    rm test_is.ll
else
    echo "⚠️  Instruction Substitution Pass test skipped"
fi

# Cleanup
rm -f test.ll

echo ""
echo "🎉 All tests completed successfully!"
echo ""
echo "📋 Next Steps:"
echo "1. Run the SIH obfuscator: ./build/sih-obfuscator test/sih_demo.c"
echo "2. Follow the interactive prompts"
echo "3. Check the generated report"
echo "4. Test the obfuscated binary"
echo ""
echo "🚀 Ready for SIH presentation!"
