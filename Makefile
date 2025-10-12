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
