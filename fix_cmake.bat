@echo off
echo Fixing CMake cache issue...
cd /d "\\wsl.localhost\Ubuntu\home\mohini\LLVMObfuscation"
wsl bash -c "cd /home/mohini/LLVMObfuscation && rm -rf build && mkdir build"
wsl bash -c "cd /home/mohini/LLVMObfuscation && cmake -B build -S . -DCMAKE_BUILD_TYPE=Release"
wsl bash -c "cd /home/mohini/LLVMObfuscation && cmake --build build"
echo Done!
pause
