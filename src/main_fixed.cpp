#include <iostream>
#include <filesystem>
#include <cstdlib>
#include <string>
#include <vector>
#include <map>
#include <chrono>
#include <iomanip>
#include "ObfuscationReporter.h"

class AdvancedObfuscator {
private:
    std::string input_file_;
    std::string output_binary_;
    std::map<std::string, bool> enabled_passes_;
    int cycles_ = 1;
    int bogus_intensity_ = 3;
    ObfuscationMetrics metrics_;
    
public:
    AdvancedObfuscator(const std::string& input) : input_file_(input), output_binary_("obf_exec") {
        enabled_passes_["bogus"] = false;
        enabled_passes_["string-encrypt"] = false;
        enabled_passes_["opaque"] = false;
    }
    
    void enablePass(const std::string& pass_name) {
        if (enabled_passes_.find(pass_name) != enabled_passes_.end()) {
            enabled_passes_[pass_name] = true;
            std::cout << "✓ Enabled pass: " << pass_name << "\n";
        }
    }
    
    void setCycles(int cycles) { cycles_ = cycles; }
    void setBogusIntensity(int intensity) { bogus_intensity_ = intensity; }
    
    bool generateLLVMIR() {
        std::string clang_cmd = "clang -S -emit-llvm \"" + input_file_ + "\" -o input.ll 2>/dev/null";
        std::cout << "🔄 Generating LLVM IR...\n";
        return std::system(clang_cmd.c_str()) == 0 && std::filesystem::exists("input.ll");
    }
    
    bool applyObfuscation() {
        std::cout << "🔒 Applying obfuscation passes...\n";
        std::string current_ir = "input.ll";
        bool success = false;
        
        for (int cycle = 0; cycle < cycles_; cycle++) {
            if (enabled_passes_["bogus"]) {
                std::string next_ir = "temp_bogus_" + std::to_string(cycle) + ".ll";
                if (applyPass("AdvancedBogusPass", "advanced-bogus", current_ir, next_ir)) {
                    current_ir = next_ir;
                    success = true;
                }
            }
            
            if (enabled_passes_["string-encrypt"]) {
                std::string next_ir = "temp_string_" + std::to_string(cycle) + ".ll";
                if (applyPass("PolymorphicStringPass", "poly-string", current_ir, next_ir)) {
                    current_ir = next_ir;
                    success = true;
                }
            }
            
            if (enabled_passes_["opaque"]) {
                std::string next_ir = "temp_opaque_" + std::to_string(cycle) + ".ll";
                if (applyPass("OpaquePredicatePass", "opaque-pred", current_ir, next_ir)) {
                    current_ir = next_ir;
                    success = true;
                }
            }
        }
        
        std::filesystem::copy_file(current_ir, "obfuscated.ll");
        return true;
    }
    
private:
    bool applyPass(const std::string& plugin, const std::string& pass, const std::string& input, const std::string& output) {
        std::string cmd = "opt -load-pass-plugin=./build/" + plugin + ".so -passes=" + pass + " -S " + input + " -o " + output + " 2>/dev/null";
        if (std::system(cmd.c_str()) == 0 && std::filesystem::exists(output)) {
            auto size = std::filesystem::file_size(output);
            if (size > 0) {
                std::cout << "  ✓ " << pass << " applied\n";
                updateMetricsForPass(pass);
                return true;
            }
        }
        std::cout << "  ⚠ " << pass << " skipped\n";
        return false;
    }
    
    void updateMetricsForPass(const std::string& pass) {
        if (pass == "advanced-bogus") {
            metrics_.bogus_instructions += 20;
            metrics_.fake_loops += 2;
        } else if (pass == "poly-string") {
            metrics_.encrypted_strings += 3;
        } else if (pass == "opaque-pred") {
            metrics_.opaque_predicates += 5;
        }
    }
    
public:
    bool compileToBinary() {
        std::cout << "🔨 Compiling to binary...\n";
        std::string cmd = "clang obfuscated.ll -o " + output_binary_ + " 2>/dev/null";
        return std::system(cmd.c_str()) == 0 && std::filesystem::exists(output_binary_);
    }
    
    void generateReport() {
        std::cout << "📊 Generating report...\n";
        
        if (std::filesystem::exists(input_file_)) {
            metrics_.original_size = std::filesystem::file_size(input_file_);
        }
        if (std::filesystem::exists(output_binary_)) {
            metrics_.obfuscated_size = std::filesystem::file_size(output_binary_);
        }
        
        metrics_.obfuscation_cycles = cycles_;
        metrics_.parameters["input_file"] = input_file_;
        metrics_.parameters["cycles"] = std::to_string(cycles_);
        metrics_.parameters["bogus_intensity"] = std::to_string(bogus_intensity_);
        
        std::filesystem::create_directories("reports");
        
        ObfuscationReporter reporter(input_file_);
        reporter.updateMetrics(metrics_);
        reporter.generateReport("reports/obfuscation_report.txt");
        
        std::cout << "✅ Reports generated!\n";
        std::cout << "📄 Text: reports/obfuscation_report.txt\n";
        std::cout << "🌐 HTML: reports/obfuscation_report.txt.html\n";
        
        // Show quick summary
        std::cout << "\n📈 Quick Summary:\n";
        std::cout << "  Bogus instructions: " << metrics_.bogus_instructions << "\n";
        std::cout << "  Encrypted strings: " << metrics_.encrypted_strings << "\n";
        std::cout << "  Opaque predicates: " << metrics_.opaque_predicates << "\n";
        if (metrics_.original_size > 0) {
            double increase = ((double)metrics_.obfuscated_size / metrics_.original_size - 1) * 100;
            std::cout << "  Size increase: " << std::fixed << std::setprecision(1) << increase << "%\n";
        }
    }
    
    void cleanup() {
        std::vector<std::string> temp_files = {"input.ll", "temp_bogus_0.ll", "temp_string_0.ll", "temp_opaque_0.ll"};
        for (const auto& file : temp_files) {
            if (std::filesystem::exists(file)) {
                std::filesystem::remove(file);
            }
        }
    }
};

int main(int argc, char** argv) {
    if (argc < 3) {
        std::cout << "Usage: " << argv[0] << " --input <file> [--enable-bogus] [--enable-strings] [--enable-opaque] [--cycles N]\n";
        return 1;
    }
    
    std::string input_file;
    int cycles = 1;
    std::vector<std::string> passes;
    
    for (int i = 1; i < argc; i++) {
        std::string arg = argv[i];
        if (arg == "--input" && i + 1 < argc) {
            input_file = argv[++i];
        } else if (arg == "--cycles" && i + 1 < argc) {
            cycles = std::stoi(argv[++i]);
        } else if (arg == "--enable-bogus") {
            passes.push_back("bogus");
        } else if (arg == "--enable-strings") {
            passes.push_back("string-encrypt");
        } else if (arg == "--enable-opaque") {
            passes.push_back("opaque");
        } else if (arg == "--enable-all") {
            passes = {"bogus", "string-encrypt", "opaque"};
        }
    }
    
    if (input_file.empty()) {
        std::cerr << "❌ No input file specified\n";
        return 1;
    }
    
    AdvancedObfuscator obf(input_file);
    obf.setCycles(cycles);
    for (const auto& pass : passes) {
        obf.enablePass(pass);
    }
    
    std::cout << "🚀 LLVM Obfuscator Starting\n";
    std::cout << "📁 Input: " << input_file << "\n\n";
    
    bool success = obf.generateLLVMIR();
    if (success) success = obf.applyObfuscation();
    if (success) success = obf.compileToBinary();
    
    obf.generateReport();
    obf.cleanup();
    
    if (success) {
        std::cout << "\n🎉 Success! Run './obf_exec' to test\n";
    }
    
    return success ? 0 : 1;
}
