Write-Host "Fixing CMake cache issue..." -ForegroundColor Green

# Navigate to the project directory
Set-Location "\\wsl.localhost\Ubuntu\home\mohini\LLVMObfuscation"

# Clean and recreate build directory
Write-Host "Cleaning build directory..." -ForegroundColor Yellow
wsl bash -c "cd /home/mohini/LLVMObfuscation && rm -rf build && mkdir build"

# Configure with CMake
Write-Host "Configuring with CMake..." -ForegroundColor Yellow
wsl bash -c "cd /home/mohini/LLVMObfuscation && cmake -B build -S . -DCMAKE_BUILD_TYPE=Release"

# Build the project
Write-Host "Building project..." -ForegroundColor Yellow
wsl bash -c "cd /home/mohini/LLVMObfuscation && cmake --build build"

Write-Host "Done!" -ForegroundColor Green
