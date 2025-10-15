cmake_minimum_required(VERSION 3.16)
project(AdvancedLLVMObfuscator)
set(CMAKE_C_COMPILER clang)
set(CMAKE_CXX_COMPILER clang++)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Find LLVM
find_package(LLVM REQUIRED CONFIG)
message(STATUS "Found LLVM ${LLVM_PACKAGE_VERSION}")
message(STATUS "Using LLVMConfig.cmake in: ${LLVM_DIR}")

# Basic include and definitions (for compatibility with older lists)
include_directories(${LLVM_INCLUDE_DIRS})
separate_arguments(LLVM_DEFINITIONS_LIST NATIVE_COMMAND ${LLVM_DEFINITIONS})
# add_definitions(${LLVM_DEFINITIONS_LIST})  # we will apply these per-target

# Map components to lib names (keep what you need)
llvm_map_components_to_libnames(llvm_libs support core irreader)

# Find llvm-config (used to extract target compile flags)
find_program(LLVM_CONFIG_EXECUTABLE llvm-config HINTS /usr/bin /usr/lib/llvm-*/bin)
if(NOT LLVM_CONFIG_EXECUTABLE)
  message(FATAL_ERROR "llvm-config not found; make sure llvm is installed and on PATH")
endif()

# get cxxflags from llvm-config and turn into a list
execute_process(COMMAND ${LLVM_CONFIG_EXECUTABLE} --cxxflags
                OUTPUT_VARIABLE LLVM_CXXFLAGS_RAW
                OUTPUT_STRIP_TRAILING_WHITESPACE)
separate_arguments(LLVM_CXXFLAGS_LIST NATIVE_COMMAND "${LLVM_CXXFLAGS_RAW}")

# Helper macro to apply LLVM flags/includes/links to a target
macro(configure_llvm_target tgt)
  target_compile_features(${tgt} PRIVATE cxx_std_17)
  target_include_directories(${tgt} PRIVATE ${LLVM_INCLUDE_DIRS})
  if(LLVM_DEFINITIONS_LIST)
    target_compile_options(${tgt} PRIVATE ${LLVM_DEFINITIONS_LIST})
  endif()
  if(LLVM_CXXFLAGS_LIST)
    target_compile_options(${tgt} PRIVATE ${LLVM_CXXFLAGS_LIST})
  endif()
endmacro()
# ===== Targets (passes) =====

add_library(AdvancedBogusPass SHARED passes/AdvancedBogusPass.cpp)
set_target_properties(AdvancedBogusPass PROPERTIES PREFIX "")
configure_llvm_target(AdvancedBogusPass)

add_library(PolymorphicStringPass SHARED passes/PolymorphicStringPass.cpp)
set_target_properties(PolymorphicStringPass PROPERTIES PREFIX "")
configure_llvm_target(PolymorphicStringPass)

add_library(CFFlattening SHARED passes/CFFlattening.cpp)
set_target_properties(CFFlattening PROPERTIES PREFIX "")
configure_llvm_target(CFFlattening)

add_library(OpaquePredicatePass SHARED passes/OpaquePredicatePass.cpp)
set_target_properties(OpaquePredicatePass PROPERTIES PREFIX "")
configure_llvm_target(OpaquePredicatePass)

# Instruction Substitution pass
add_library(InstructionSubstitutionPass SHARED passes/InstructionSubstitutionPass.cpp)
set_target_properties(InstructionSubstitutionPass PROPERTIES PREFIX "")
configure_llvm_target(InstructionSubstitutionPass)


# ===== Main CLI application =====
add_executable(advanced-obfuscator src/main.cpp src/ObfuscationReporter.cpp)
# your main likely doesn't need the same compile options, but link it to llvm libs if required
target_compile_features(advanced-obfuscator PRIVATE cxx_std_17)
target_include_directories(advanced-obfuscator PRIVATE ${LLVM_INCLUDE_DIRS})
target_link_libraries(advanced-obfuscator PRIVATE ${llvm_libs})

# ===== SIH Enhanced application =====
add_executable(sih-obfuscator
  src/main_enhanced.cpp
  src/SIHObfuscationReporter.cpp
  src/ObfuscationReporter.cpp
)
target_compile_features(sih-obfuscator PRIVATE cxx_std_17)
target_include_directories(sih-obfuscator PRIVATE ${LLVM_INCLUDE_DIRS})
target_link_libraries(sih-obfuscator PRIVATE ${llvm_libs})