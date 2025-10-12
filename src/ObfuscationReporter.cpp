#include "ObfuscationReporter.h"
#include <fstream>
#include <iostream>
#include <filesystem>
#include <chrono>
#include <iomanip>
#include <sstream>

ObfuscationReporter::ObfuscationReporter(const std::string& input_file) 
    : input_file_(input_file) {
    if (std::filesystem::exists(input_file)) {
        metrics_.original_size = std::filesystem::file_size(input_file);
    }
}

void ObfuscationReporter::updateMetrics(const ObfuscationMetrics& metrics) {
    metrics_ = metrics;
    // The original size was set in the constructor. Don't overwrite it.
    metrics_.original_size = std::filesystem::file_size(input_file_);
    calculateSizeIncrease();
}

void ObfuscationReporter::calculateSizeIncrease() {
    if (std::filesystem::exists("obf_exec")) {
        metrics_.obfuscated_size = std::filesystem::file_size("obf_exec");
    }
}

std::string ObfuscationReporter::getCurrentTimestamp() {
    auto now = std::chrono::system_clock::now();
    auto time_t_now = std::chrono::system_clock::to_time_t(now);
    std::tm local_tm;
    
    // Use platform-specific safe functions for localtime
    #ifdef _WIN32
        localtime_s(&local_tm, &time_t_now);
    #else
        localtime_r(&time_t_now, &local_tm);
    #endif

    std::stringstream ss;
    ss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
    return ss.str();
}

void ObfuscationReporter::generateReport(const std::string& output_file) {
    std::ofstream report(output_file);
    
    report << "=== ADVANCED LLVM OBFUSCATION REPORT ===\n";
    report << "Generated: " << getCurrentTimestamp() << "\n\n";
    
    report << "INPUT PARAMETERS:\n";
    for (const auto& param : metrics_.parameters) {
        report << "  " << param.first << ": " << param.second << "\n";
    }
    
    report << "\nOBFUSCATION METRICS:\n";
    report << "  Obfuscation Cycles: " << metrics_.obfuscation_cycles << "\n";
    report << "  Bogus Instructions Added: " << metrics_.bogus_instructions << "\n";
    report << "  Strings Encrypted: " << metrics_.encrypted_strings << "\n";
    report << "  Fake Loops Inserted: " << metrics_.fake_loops << "\n";
    report << "  Functions Flattened: " << metrics_.flattened_functions << "\n";
    report << "  Opaque Predicates Added: " << metrics_.opaque_predicates << "\n";
    report << "  Functions Split: " << metrics_.split_functions << "\n";
    
    report << "\nFILE SIZE ANALYSIS:\n";
    report << "  Original Size: " << metrics_.original_size << " bytes\n";
    report << "  Obfuscated Size: " << metrics_.obfuscated_size << " bytes\n";
    if (metrics_.original_size > 0) {
        double increase = ((double)metrics_.obfuscated_size / metrics_.original_size - 1) * 100;
        report << "  Size Increase: " << std::fixed << std::setprecision(2) << increase << "%\n";
    } else {
        report << "  Size Increase: N/A\n";
    }
    
    report << "\nPERFORMANCE IMPACT:\n";
    report << "  Estimated Execution Overhead: " << 
              std::fixed << std::setprecision(2) << metrics_.execution_time_overhead << "%\n";
    
    // Generate HTML version
    generateHTMLReport(output_file + ".html");
}

void ObfuscationReporter::generateHTMLReport(const std::string& output_file) {
    std::ofstream html(output_file);
    double increase = 0.0;
    if (metrics_.original_size > 0) {
        increase = ((double)metrics_.obfuscated_size / metrics_.original_size - 1) * 100;
    }

    html << R"(
<!DOCTYPE html>
<html>
<head>
    <title>LLVM Obfuscation Report</title>
    <style>
        body { font-family: 'Segoe UI', Arial, sans-serif; margin: 40px; background: #f5f5f5; }
        .container { background: white; padding: 30px; border-radius: 10px; box-shadow: 0 2px 10px rgba(0,0,0,0.1); }
        h1 { color: #2c3e50; border-bottom: 3px solid #3498db; padding-bottom: 10px; }
        h2 { color: #34495e; margin-top: 30px; }
        .metric-grid { display: grid; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); gap: 20px; margin: 20px 0; }
        .metric-card { background: #ecf0f1; padding: 15px; border-radius: 8px; text-align: center; }
        .metric-value { font-size: 24px; font-weight: bold; color: #2980b9; }
        .metric-label { color: #7f8c8d; margin-top: 5px; }
        table { width: 100%; border-collapse: collapse; margin: 20px 0; }
        th, td { padding: 12px; text-align: left; border-bottom: 1px solid #ddd; }
        th { background-color: #34495e; color: white; }
        .success { color: #27ae60; font-weight: bold; }
        .warning { color: #f39c12; font-weight: bold; }
    </style>
</head>
<body>
    <div class="container">
        <h1>🔒 Advanced LLVM Obfuscation Report</h1>
        <p><strong>Generated:</strong> )" << getCurrentTimestamp() << R"(</p>
        
        <h2>📊 Obfuscation Metrics</h2>
        <div class="metric-grid">
            <div class="metric-card">
                <div class="metric-value">)" << metrics_.obfuscation_cycles << R"(</div>
                <div class="metric-label">Obfuscation Cycles</div>
            </div>
            <div class="metric-card">
                <div class="metric-value">)" << metrics_.bogus_instructions << R"(</div>
                <div class="metric-label">Bogus Instructions</div>
            </div>
            <div class="metric-card">
                <div class="metric-value">)" << metrics_.encrypted_strings << R"(</div>
                <div class="metric-label">Encrypted Strings</div>
            </div>
            <div class="metric-card">
                <div class="metric-value">)" << metrics_.fake_loops << R"(</div>
                <div class="metric-label">Fake Loops</div>
            </div>
        </div>
        
        <h2>📈 Size Analysis</h2>
        <table>
            <tr><th>Metric</th><th>Value</th></tr>
            <tr><td>Original Size</td><td>)" << metrics_.original_size << R"( bytes</td></tr>
            <tr><td>Obfuscated Size</td><td>)" << metrics_.obfuscated_size << R"( bytes</td></tr>
            <tr><td>Size Increase</td><td class="warning">)" << std::fixed << std::setprecision(2) << increase << R"(%</td></tr>
        </table>
    </div>
</body>
</html>)";
}
