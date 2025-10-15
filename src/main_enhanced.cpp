#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <limits>
#include <fstream>
#include "ObfuscationReporter.h"

// Enhanced configuration structure for SIH requirements
struct SIHConfiguration {
    // Platform/Target settings
    std::string target_platform = "linux";  // "windows" or "linux"
    std::string target_arch = "x64";         // "x86", "x64", "arm"
    std::string calling_convention = "cdecl";
    
    // Performance/Size budget
    double max_size_increase = 1000.0;      // Maximum % size increase allowed
    double max_runtime_overhead = 50.0;     // Maximum % runtime overhead allowed
    bool enforce_limits = false;             // Whether to enforce limits strictly
    
    // Obfuscation cycles
    int num_cycles = 1;
    
    // Technique selection and aggressiveness
    struct TechniqueConfig {
        bool enabled = false;
        int intensity = 3;  // 1-5 scale
        double aggressiveness = 0.5;  // 0.0-1.0 scale
    };
    
    std::map<std::string, TechniqueConfig> techniques = {
        {"control_flow_flattening", {false, 3, 0.5}},
        {"bogus_control_flow", {false, 3, 0.5}},
        {"string_encryption", {false, 3, 0.5}},
        {"instruction_substitution", {false, 3, 0.5}},
        {"opaque_predicates", {false, 3, 0.5}},
        {"function_splitting", {false, 3, 0.5}},
        {"symbol_stripping", {false, 3, 0.5}},
        {"anti_disassembly", {false, 3, 0.5}}
    };
    
    // Output settings
    std::string output_binary = "obfuscated_binary";
    std::string report_file = "sih_obfuscation_report.txt";
};

class SIHObfuscator {
private:
    void parseAndAccumulateMetrics(const std::string& pass, const std::string& logPath, int cycle) {
        std::ifstream in(logPath);
        if (!in.good()) return;
        std::string line;
        while (std::getline(in, line)) {
            if (pass == "cf-flatten") {
                // Example: CFFlattening: Flattened 3 functions
                auto pos = line.find("Flattened ");
                if (pos != std::string::npos) {
                    pos += std::string("Flattened ").size();
                    size_t end = line.find(' ', pos);
                    int n = std::stoi(line.substr(pos, end - pos));
                    metrics_.flattened_functions += n;
                }
            } else if (pass == "advanced-bogus") {
                // Example: AdvancedBogusPass: Added 127 bogus instructions
                auto pos = line.find("Added ");
                if (pos != std::string::npos) {
                    pos += std::string("Added ").size();
                    size_t end = line.find(' ', pos);
                    int n = std::stoi(line.substr(pos, end - pos));
                    metrics_.bogus_instructions += n;
                }
            } else if (pass == "poly-string") {
                // Example: PolymorphicStringPass: Encrypted 13 strings
                auto pos = line.find("Encrypted ");
                if (pos != std::string::npos) {
                    pos += std::string("Encrypted ").size();
                    size_t end = line.find(' ', pos);
                    int n = std::stoi(line.substr(pos, end - pos));
                    metrics_.encrypted_strings += n;
                }
            } else if (pass == "opaque-pred") {
                // Example: OpaquePredicatePass: Added 55 opaque predicates
                auto pos = line.find("Added ");
                if (pos != std::string::npos) {
                    pos += std::string("Added ").size();
                    size_t end = line.find(' ', pos);
                    int n = std::stoi(line.substr(pos, end - pos));
                    metrics_.opaque_predicates += n;
                }
            } else if (pass == "inst-subst") {
                // Example line from pass: InstructionSubstitution: Applied 7 substitutions
                auto pos = line.find("Applied ");
                if (pos != std::string::npos) {
                    pos += std::string("Applied ").size();
                    size_t end = line.find(' ', pos);
                    int n = std::stoi(line.substr(pos, end - pos));
                    if ((int)metrics_.instruction_substitutions_per_cycle.size() <= cycle) {
                        metrics_.instruction_substitutions_per_cycle.resize(cycle + 1, 0);
                    }
                    metrics_.instruction_substitutions_per_cycle[cycle] += n;
                    metrics_.instruction_substitutions_total += n;
                    metrics_.parameters["instruction_substitutions_total"] = std::to_string(metrics_.instruction_substitutions_total);
                }
            }
        }
    }
    std::string input_file_;
    SIHConfiguration config_;
    ObfuscationMetrics metrics_;
    
    // Interactive input methods
    void collectPlatformSettings() {
        std::cout << "\n🖥️  PLATFORM & TARGET CONFIGURATION\n";
        std::cout << "=====================================\n";
        
        // Platform selection
        std::cout << "Select target platform:\n";
        std::cout << "1. Linux\n";
        std::cout << "2. Windows\n";
        std::cout << "Choice (1-2): ";
        
        int platform_choice;
        std::cin >> platform_choice;
        config_.target_platform = (platform_choice == 2) ? "windows" : "linux";
        
        // Architecture selection
        std::cout << "\nSelect target architecture:\n";
        std::cout << "1. x86 (32-bit)\n";
        std::cout << "2. x64 (64-bit)\n";
        std::cout << "3. ARM\n";
        std::cout << "Choice (1-3): ";
        
        int arch_choice;
        std::cin >> arch_choice;
        switch(arch_choice) {
            case 1: config_.target_arch = "x86"; break;
            case 2: config_.target_arch = "x64"; break;
            case 3: config_.target_arch = "arm"; break;
            default: config_.target_arch = "x64"; break;
        }
        
        std::cout << "✓ Target: " << config_.target_platform << " " << config_.target_arch << "\n";
    }
    
    void collectPerformanceSettings() {
        std::cout << "\n⚡ PERFORMANCE & SIZE BUDGET\n";
        std::cout << "============================\n";
        
        std::cout << "Maximum allowed size increase (%): ";
        std::cin >> config_.max_size_increase;
        
        std::cout << "Maximum allowed runtime overhead (%): ";
        std::cin >> config_.max_runtime_overhead;
        
        std::cout << "Enforce limits strictly? (y/n): ";
        char enforce;
        std::cin >> enforce;
        config_.enforce_limits = (enforce == 'y' || enforce == 'Y');
        
        std::cout << "✓ Performance limits set\n";
    }
    
    void collectCycleSettings() {
        std::cout << "\n🔄 OBFUSCATION CYCLES\n";
        std::cout << "=====================\n";
        
        std::cout << "Number of obfuscation cycles (1-10): ";
        std::cin >> config_.num_cycles;
        config_.num_cycles = std::max(1, std::min(10, config_.num_cycles));
        
        std::cout << "✓ Cycles set to: " << config_.num_cycles << "\n";
    }
    
    void collectTechniqueSettings() {
        std::cout << "\n🔧 OBFUSCATION TECHNIQUES\n";
        std::cout << "=========================\n";
        
        std::vector<std::string> technique_names = {
            "Control Flow Flattening",
            "Bogus Control Flow", 
            "String Encryption",
            "Instruction Substitution",
            "Opaque Predicates"
        };
        
        std::vector<std::string> technique_keys = {
            "control_flow_flattening",
            "bogus_control_flow",
            "string_encryption", 
            "instruction_substitution",
            "opaque_predicates"
        };
        
        for (size_t i = 0; i < technique_names.size(); i++) {
            std::cout << "\n" << (i+1) << ". " << technique_names[i] << "\n";
            std::cout << "   Enable? (y/n): ";
            char enable;
            std::cin >> enable;
            
            if (enable == 'y' || enable == 'Y') {
                config_.techniques[technique_keys[i]].enabled = true;
                
                std::cout << "   Intensity (1-5): ";
                std::cin >> config_.techniques[technique_keys[i]].intensity;
                config_.techniques[technique_keys[i]].intensity = 
                    std::max(1, std::min(5, config_.techniques[technique_keys[i]].intensity));
                
                std::cout << "   Aggressiveness (0.0-1.0): ";
                std::cin >> config_.techniques[technique_keys[i]].aggressiveness;
                config_.techniques[technique_keys[i]].aggressiveness = 
                    std::max(0.0, std::min(1.0, config_.techniques[technique_keys[i]].aggressiveness));
                
                std::cout << "   ✓ Enabled with intensity " << config_.techniques[technique_keys[i]].intensity 
                         << " and aggressiveness " << std::fixed << std::setprecision(1) 
                         << config_.techniques[technique_keys[i]].aggressiveness << "\n";
            }
        }
    }
    
    void collectOutputSettings() {
        std::cout << "\n📁 OUTPUT SETTINGS\n";
        std::cout << "==================\n";
        
        std::cout << "Output binary name: ";
        std::cin >> config_.output_binary;
        
        std::cout << "Report file name: ";
        std::cin >> config_.report_file;
        
        std::cout << "✓ Output settings configured\n";
    }
    
    void displayConfiguration() {
        std::cout << "\n📋 CONFIGURATION SUMMARY\n";
        std::cout << "========================\n";
        std::cout << "Target Platform: " << config_.target_platform << " " << config_.target_arch << "\n";
        std::cout << "Max Size Increase: " << config_.max_size_increase << "%\n";
        std::cout << "Max Runtime Overhead: " << config_.max_runtime_overhead << "%\n";
        std::cout << "Obfuscation Cycles: " << config_.num_cycles << "\n";
        std::cout << "Output Binary: " << config_.output_binary << "\n";
        std::cout << "Report File: " << config_.report_file << "\n";
        
        std::cout << "\nEnabled Techniques:\n";
        auto printIf = [&](const std::string& key, const std::string& label){
            const auto& t = config_.techniques[key];
            if (t.enabled) {
                std::cout << "  ✓ " << label << " (intensity: " << t.intensity
                          << ", aggressiveness: " << std::fixed << std::setprecision(1)
                          << t.aggressiveness << ")\n";
            }
        };
        printIf("control_flow_flattening", "control_flow_flattening");
        printIf("bogus_control_flow", "bogus_control_flow");
        printIf("instruction_substitution", "instruction_substitution");
        printIf("string_encryption", "string_encryption");
        printIf("opaque_predicates", "opaque_predicates");
    }
    
public:
    SIHObfuscator(const std::string& input_file) : input_file_(input_file) {
        // Initialize metrics
        metrics_.parameters["input_file"] = input_file;
    }
    
    void collectUserInput() {
        std::cout << "🔒 SIH LLVM OBFUSCATOR - INTERACTIVE CONFIGURATION\n";
        std::cout << "==================================================\n";
        std::cout << "Input file: " << input_file_ << "\n\n";
        
        collectPlatformSettings();
        collectPerformanceSettings();
        collectCycleSettings();
        collectTechniqueSettings();
        collectOutputSettings();
        
        displayConfiguration();
        
        std::cout << "\nProceed with obfuscation? (y/n): ";
        char proceed;
        std::cin >> proceed;
        
        if (proceed != 'y' && proceed != 'Y') {
            std::cout << "❌ Obfuscation cancelled by user\n";
            exit(0);
        }
    }
    
    bool generateLLVMIR() {
        std::cout << "\n🔄 GENERATING LLVM IR\n";
        std::cout << "=====================\n";
        
        // Build clang command with target specifications
        std::string clang_cmd = "clang -S -emit-llvm";
        
        // Map architecture to valid LLVM target triple arch names
        std::string archTriple = config_.target_arch;
        if (archTriple == "x64") archTriple = "x86_64";
        else if (archTriple == "x86") archTriple = "i386";
        
        // Add target-specific flags
        if (config_.target_platform == "windows") {
            clang_cmd += " -target " + archTriple + "-pc-windows-msvc";
        } else {
            clang_cmd += " -target " + archTriple + "-pc-linux-gnu";
        }
        
        clang_cmd += " \"" + input_file_ + "\" -o input.ll";
        
        std::cout << "Command: " << clang_cmd << "\n";
        int rc = std::system(clang_cmd.c_str());
        if (rc != 0 || !std::filesystem::exists("input.ll")) {
            std::cout << "Primary IR generation failed. Trying fallback without explicit target...\n";
            std::string fallback;
            if (config_.target_platform == "linux" && config_.target_arch == "x86") {
                // Try 32-bit mode on host if multilib is available
                fallback = "clang -m32 -S -emit-llvm \"" + input_file_ + "\" -o input.ll";
            } else {
                // Host default triple
                fallback = "clang -S -emit-llvm \"" + input_file_ + "\" -o input.ll";
            }
            std::cout << "Command: " << fallback << "\n";
            rc = std::system(fallback.c_str());
        }
        return rc == 0 && std::filesystem::exists("input.ll");
    }
    
    bool applyObfuscation() {
        std::cout << "\n🔒 APPLYING OBFUSCATION PASSES\n";
        std::cout << "===============================\n";
        
        std::string current_ir = "input.ll";
        bool success = false;
        
        std::cout << "\n🔒 Applying enabled passes...\n";
        for (int cycle = 0; cycle < config_.num_cycles; cycle++) {
            std::cout << "\n--- Cycle " << (cycle + 1) << "/" << config_.num_cycles << " ---\n";
            
            // Apply each enabled technique in a safer order:
            // 1) Control Flow Flattening
            if (config_.techniques["control_flow_flattening"].enabled) {
                std::string next_ir = "temp_cf_" + std::to_string(cycle) + ".ll";
                if (applyPass("CFFlattening", "cf-flatten", current_ir, next_ir, cycle)) {
                    current_ir = next_ir;
                    success = true;
                }
            }

            // 2) Bogus Control Flow
            if (config_.techniques["bogus_control_flow"].enabled) {
                std::string next_ir = "temp_bogus_" + std::to_string(cycle) + ".ll";
                if (applyPass("AdvancedBogusPass", "advanced-bogus", current_ir, next_ir, cycle)) {
                    current_ir = next_ir;
                    success = true;
                }
            }

            // 3) Instruction Substitution
            if (config_.techniques["instruction_substitution"].enabled) {
                std::string next_ir = "temp_is_" + std::to_string(cycle) + ".ll";
                if (applyPass("InstructionSubstitutionPass", "inst-subst", current_ir, next_ir, cycle)) {
                    current_ir = next_ir;
                    success = true;
                }
            }

            // 4) Opaque Predicates
            if (config_.techniques["opaque_predicates"].enabled) {
                std::string next_ir = "temp_opaque_" + std::to_string(cycle) + ".ll";
                if (applyPass("OpaquePredicatePass", "opaque-pred", current_ir, next_ir, cycle)) {
                    current_ir = next_ir;
                    success = true;
                }
            }

            // 5) String Encryption (order-independent)
            if (config_.techniques["string_encryption"].enabled) {
                std::string next_ir = "temp_string_" + std::to_string(cycle) + ".ll";
                if (applyPass("PolymorphicStringPass", "poly-string", current_ir, next_ir, cycle)) {
                    current_ir = next_ir;
                    success = true;
                }
            }
        }
        
        // Only produce obfuscated.ll if at least one pass succeeded
        if (success && std::filesystem::exists(current_ir)) {
            std::error_code ec;
            std::filesystem::copy_file(current_ir, "obfuscated.ll",
                                       std::filesystem::copy_options::overwrite_existing, ec);
        } else {
            std::cout << "No obfuscation pass produced output; aborting.\n";
        }
        return success;
    }
    
private:
    bool applyPass(const std::string& plugin, const std::string& pass, 
                   const std::string& input, const std::string& output, int cycle) {
        // Build absolute paths for reliability
        const auto cwd = std::filesystem::current_path();
        const std::string pluginPath = (cwd / ("build/" + plugin + ".so")).string();
        const std::string inputPath = (std::filesystem::path(input).is_absolute() ? input : (cwd / input).string());
        const std::string outputPath = (std::filesystem::path(output).is_absolute() ? output : (cwd / output).string());

        // Log file to capture pass stdout for metrics parsing
        const std::string logPath = (cwd / ("pass_" + pass + "_cycle_" + std::to_string(cycle) + ".log")).string();
        std::string cmd = "opt -load-pass-plugin=" + pluginPath + " -passes=" + pass +
                          " -S \"" + inputPath + "\" -o \"" + outputPath + "\" > \"" + logPath + "\" 2>&1";
        std::cout << "Running: " << cmd << "\n";

        if (std::system(cmd.c_str()) == 0 && std::filesystem::exists(outputPath)) {
            auto size = std::filesystem::file_size(outputPath);
            if (size > 0) {
                std::cout << "  ✓ " << pass << " applied (cycle " << (cycle + 1) << ")\n";
                // Prefer precise pass-reported counts
                parseAndAccumulateMetrics(pass, logPath, cycle);
                return true;
            }
        }
        std::cout << "  ⚠ " << pass << " skipped or failed (cycle " << (cycle + 1) << ")\n";
        return false;
    }
    
    void updateMetricsForPass(const std::string& pass, int cycle) {
        // Update metrics based on technique and intensity
        auto technique = config_.techniques.begin();
        for (; technique != config_.techniques.end(); ++technique) {
            if (pass.find(technique->first.substr(0, 3)) != std::string::npos) {
                break;
            }
        }
        
        if (technique != config_.techniques.end()) {
            int intensity = technique->second.intensity;
            double aggressiveness = technique->second.aggressiveness;
            
            if (pass == "advanced-bogus") {
                metrics_.bogus_instructions += 20 * intensity * aggressiveness;
                metrics_.fake_loops += 2 * intensity * aggressiveness;
            } else if (pass == "poly-string") {
                metrics_.encrypted_strings += 3 * intensity * aggressiveness;
            } else if (pass == "inst-subst") {
                // Set a parameter; precise count comes from log parsing
                int approx = 2 * intensity * aggressiveness;
                int current = 0;
                if (metrics_.parameters.count("instruction_substitutions_total")) {
                    current = std::stoi(metrics_.parameters["instruction_substitutions_total"]);
                }
                metrics_.parameters["instruction_substitutions_total"] = std::to_string(current + approx);
            } else if (pass == "opaque-pred") {
                metrics_.opaque_predicates += 5 * intensity * aggressiveness;
            } else if (pass == "cf-flatten") {
                metrics_.flattened_functions += 1 * intensity * aggressiveness;
            }
        }
    }
    
public:
    bool compileToBinary() {
        std::cout << "\n🔨 COMPILING TO BINARY\n";
        std::cout << "=====================\n";
        
        // Map arch
        std::string archTriple = config_.target_arch;
        if (archTriple == "x64") archTriple = "x86_64";
        else if (archTriple == "x86") archTriple = "i386";

        // First attempt: direct clang link from LLVM IR with appropriate flags
        std::string cmd;
        if (config_.target_platform == "windows") {
            // Prefer MinGW on Linux for Windows targets if available
            std::string mingw = (archTriple == "i386") ? "i686-w64-mingw32" : "x86_64-w64-mingw32";
            std::string mingwClang = "clang --target=" + mingw;
            cmd = mingwClang + " obfuscated.ll -o " + config_.output_binary + " -Wl,--subsystem,console";
        } else {
            if (archTriple == "i386") {
                cmd = "clang -m32 obfuscated.ll -o " + config_.output_binary;
            } else {
                cmd = "clang -target " + archTriple + "-pc-linux-gnu obfuscated.ll -o " + config_.output_binary;
            }
        }
        std::cout << "Command: " << cmd << "\n";
        int rc = std::system(cmd.c_str());
        bool success = (rc == 0) && std::filesystem::exists(config_.output_binary);
        
        // Fallback: llc to object, then link with clang
        if (!success) {
            std::cout << "Primary link failed. Trying llc + clang fallback...\n";
            std::string objFile = "obf.o";
            std::string llcCmd;
            if (config_.target_platform == "windows") {
                std::string mingw = (archTriple == "i386") ? "i686-w64-mingw32" : "x86_64-w64-mingw32";
                llcCmd = "llc -filetype=obj -mtriple=" + mingw + " obfuscated.ll -o " + objFile;
            } else {
                llcCmd = "llc -filetype=obj -mtriple=" + archTriple + "-pc-linux-gnu obfuscated.ll -o " + objFile;
            }
            std::cout << "Command: " << llcCmd << "\n";
            rc = std::system(llcCmd.c_str());
            if (rc == 0 && std::filesystem::exists(objFile)) {
                std::string linkCmd;
                if (config_.target_platform == "windows") {
                    std::string mingw = (archTriple == "i386") ? "i686-w64-mingw32" : "x86_64-w64-mingw32";
                    linkCmd = "clang --target=" + mingw + " " + objFile + " -o " + config_.output_binary + " -Wl,--subsystem,console";
                } else {
                    if (archTriple == "i386") linkCmd = "clang -m32 " + objFile + " -o " + config_.output_binary;
                    else linkCmd = "clang " + objFile + " -o " + config_.output_binary;
                }
                std::cout << "Command: " << linkCmd << "\n";
                rc = std::system(linkCmd.c_str());
                success = (rc == 0) && std::filesystem::exists(config_.output_binary);
            }
        }
        
        if (success) {
            std::cout << "✓ Binary generated: " << config_.output_binary << "\n";
        } else {
            std::cout << "❌ Binary compilation failed\n";
            if (config_.target_platform == "windows") {
                std::cout << "Hint: On Linux, install MinGW toolchain for Windows targets: sudo apt install -y clang binutils-mingw-w64 gcc-mingw-w64\n";
            }
        }
        
        return success;
    }
    
    void generateSIHReport() {
        std::cout << "\n📊 GENERATING SIH REPORT\n";
        std::cout << "========================\n";
        
        // Update metrics with configuration
        metrics_.obfuscation_cycles = config_.num_cycles;
        metrics_.parameters["target_platform"] = config_.target_platform;
        metrics_.parameters["target_arch"] = config_.target_arch;
        metrics_.parameters["max_size_increase"] = std::to_string(config_.max_size_increase);
        metrics_.parameters["max_runtime_overhead"] = std::to_string(config_.max_runtime_overhead);
        // Expose per-cycle substitutions in parameters for legacy consumers
        if (!metrics_.instruction_substitutions_per_cycle.empty()) {
            for (size_t i = 0; i < metrics_.instruction_substitutions_per_cycle.size(); ++i) {
                metrics_.parameters["instruction_substitutions_cycle_" + std::to_string(i+1)] =
                    std::to_string(metrics_.instruction_substitutions_per_cycle[i]);
            }
            metrics_.parameters["instruction_substitutions_total"] = std::to_string(metrics_.instruction_substitutions_total);
        }
        
        // Add technique-specific parameters (only supported techniques)
        for (const auto& [name, tech_config] : config_.techniques) {
            if (name == "control_flow_flattening" || name == "bogus_control_flow" ||
                name == "string_encryption" || name == "instruction_substitution" ||
                name == "opaque_predicates") {
                if (tech_config.enabled) {
                    metrics_.parameters[name + "_enabled"] = "true";
                    metrics_.parameters[name + "_intensity"] = std::to_string(tech_config.intensity);
                    metrics_.parameters[name + "_aggressiveness"] = std::to_string(tech_config.aggressiveness);
                }
            }
        }
        
        // Calculate file sizes
        if (std::filesystem::exists(input_file_)) {
            metrics_.original_size = std::filesystem::file_size(input_file_);
        }
        if (std::filesystem::exists(config_.output_binary)) {
            metrics_.obfuscated_size = std::filesystem::file_size(config_.output_binary);
        }
        
        // Create reports directory
        std::filesystem::create_directories("reports");
        
        // Generate enhanced report
        ObfuscationReporter reporter(input_file_);
        reporter.updateMetrics(metrics_);
        // Best-effort placeholders for practical evaluation metrics (compute externally if needed)
        if (!metrics_.parameters.count("decompiler_intelligibility_qualitative"))
            metrics_.decompiler_intelligibility_qualitative = "N/A";
        if (!metrics_.parameters.count("decompiler_intelligibility_score"))
            metrics_.decompiler_intelligibility_score = -1.0;
        if (!metrics_.parameters.count("red_team_recovery_time_minutes"))
            metrics_.red_team_recovery_time_minutes = -1.0;
        if (!metrics_.parameters.count("instruction_entropy"))
            metrics_.instruction_entropy = -1.0;
        if (!metrics_.parameters.count("cfg_edge_density"))
            metrics_.cfg_edge_density = -1.0;
        if (!metrics_.parameters.count("similarity_original_vs_decompiled"))
            metrics_.similarity_original_vs_decompiled = -1.0;
        if (!metrics_.parameters.count("automated_deobfuscator_success_rate"))
            metrics_.automated_deobfuscator_success_rate = -1.0;
        reporter.generateReport("reports/" + config_.report_file);
        
        std::cout << "✅ SIH Report generated!\n";
        std::cout << "📄 Text: reports/" << config_.report_file << "\n";
        std::cout << "🌐 HTML: reports/" << config_.report_file << ".html\n";
        
        // Display SIH-specific summary
        displaySIHSummary();
    }
    
    void displaySIHSummary() {
        std::cout << "\n📈 SIH OBFUSCATION SUMMARY\n";
        std::cout << "==========================\n";
        std::cout << "a. Input Parameters Logged: ✓\n";
        std::cout << "b. Output File Attributes: ✓\n";
        std::cout << "   - Size: " << metrics_.obfuscated_size << " bytes\n";
        std::cout << "   - Platform: " << config_.target_platform << " " << config_.target_arch << "\n";
        std::cout << "c. Bogus Code Generated: " << metrics_.bogus_instructions << " instructions\n";
        std::cout << "d. Obfuscation Cycles: " << metrics_.obfuscation_cycles << "\n";
        std::cout << "e. String Encryption: " << metrics_.encrypted_strings << " strings\n";
        std::cout << "f. Fake Loops Inserted: " << metrics_.fake_loops << "\n";
        if (!metrics_.instruction_substitutions_per_cycle.empty()) {
            std::cout << "h. Instruction Substitutions (per cycle): ";
            for (size_t i = 0; i < metrics_.instruction_substitutions_per_cycle.size(); ++i) {
                if (i) std::cout << ", ";
                std::cout << "cycle " << (i + 1) << ": " << metrics_.instruction_substitutions_per_cycle[i];
            }
            std::cout << "\n";
            std::cout << "   Total Instruction Substitutions: " << metrics_.instruction_substitutions_total << "\n";
        }
        
        if (metrics_.original_size > 0) {
            double increase = ((double)metrics_.obfuscated_size / metrics_.original_size - 1) * 100;
            std::cout << "g. Size Increase: " << std::fixed << std::setprecision(2) << increase << "%\n";
            
            if (config_.enforce_limits && increase > config_.max_size_increase) {
                std::cout << "⚠️  WARNING: Size increase exceeds limit!\n";
            }
        }
    }
    
    void cleanup() {
        std::vector<std::string> temp_files = {
            "input.ll", "obfuscated.ll"
        };
        
        // Add cycle-specific temp files (only supported techniques)
        for (int i = 0; i < config_.num_cycles; i++) {
            temp_files.push_back("temp_cf_" + std::to_string(i) + ".ll");
            temp_files.push_back("temp_bogus_" + std::to_string(i) + ".ll");
            temp_files.push_back("temp_string_" + std::to_string(i) + ".ll");
            temp_files.push_back("temp_opaque_" + std::to_string(i) + ".ll");
        }
        
        for (const auto& file : temp_files) {
            if (std::filesystem::exists(file)) {
                std::filesystem::remove(file);
            }
        }
    }
};

int main(int argc, char** argv) {
    if (argc < 2) {
        std::cout << "🔒 SIH LLVM OBFUSCATOR\n";
        std::cout << "======================\n";
        std::cout << "Usage: " << argv[0] << " <input_file.c>\n";
        std::cout << "\nThis tool will guide you through the obfuscation configuration.\n";
        return 1;
    }
    
    std::string input_file = argv[1];
    
    if (!std::filesystem::exists(input_file)) {
        std::cerr << "❌ Input file not found: " << input_file << "\n";
        return 1;
    }
    
    SIHObfuscator obf(input_file);
    bool success = false;
    
    try {
        obf.collectUserInput();
        
        std::cout << "\n🚀 STARTING OBFUSCATION PROCESS\n";
        std::cout << "================================\n";
        
        success = obf.generateLLVMIR();
        if (success) success = obf.applyObfuscation();
        if (success) success = obf.compileToBinary();
        
        obf.generateSIHReport();
        obf.cleanup();
        
        if (success) {
            std::cout << "\n🎉 SIH OBFUSCATION COMPLETED SUCCESSFULLY!\n";
            std::cout << "==========================================\n";
            std::cout << "Run the obfuscated binary: ./" << input_file.substr(0, input_file.find('.')) << "_obfuscated\n";
        } else {
            std::cout << "\n❌ Obfuscation failed. Check the error messages above.\n";
        }
        
    } catch (const std::exception& e) {
        std::cerr << "❌ Error: " << e.what() << "\n";
        return 1;
    }
    
    return success ? 0 : 1;
}
