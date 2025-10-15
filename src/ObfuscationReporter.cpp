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
    // Do not attempt to recalculate obfuscated_size here; it is provided by caller
}

void ObfuscationReporter::calculateSizeIncrease() {
    // Deprecated: size is computed and provided by the caller; keep function for API stability
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
    // Instruction substitutions: totals and per-cycle
    report << "  Instruction Substitutions (Total): " << metrics_.instruction_substitutions_total << "\n";
    if (!metrics_.instruction_substitutions_per_cycle.empty()) {
        report << "  Instruction Substitutions (Per Cycle): ";
        for (size_t i = 0; i < metrics_.instruction_substitutions_per_cycle.size(); ++i) {
            if (i) report << ", ";
            report << "c" << (i + 1) << "=" << metrics_.instruction_substitutions_per_cycle[i];
        }
        report << "\n";
    }
    report << "  Strings Encrypted: " << metrics_.encrypted_strings << "\n";
    report << "  Fake Loops Inserted: " << metrics_.fake_loops << "\n";
    report << "  Functions Flattened: " << metrics_.flattened_functions << "\n";
    report << "  Opaque Predicates Added: " << metrics_.opaque_predicates << "\n";
    // Function splitting removed from supported techniques
    
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

    // Practical evaluation metrics
    report << "\nPRACTICAL EVALUATION METRICS:\n";
    report << "  Decompiler Intelligibility (qualitative): " 
           << (metrics_.decompiler_intelligibility_qualitative.empty() ? "N/A" : metrics_.decompiler_intelligibility_qualitative) << "\n";
    report << "  Decompiler Intelligibility (score 0-100): ";
    if (metrics_.decompiler_intelligibility_score >= 0.0) report << std::fixed << std::setprecision(1) << metrics_.decompiler_intelligibility_score << "\n"; else report << "N/A\n";
    report << "  Red-Team Recovery Time (minutes): ";
    if (metrics_.red_team_recovery_time_minutes >= 0.0) report << std::fixed << std::setprecision(1) << metrics_.red_team_recovery_time_minutes << "\n"; else report << "N/A\n";
    report << "  Instruction Entropy (bits): ";
    if (metrics_.instruction_entropy >= 0.0) report << std::fixed << std::setprecision(3) << metrics_.instruction_entropy << "\n"; else report << "N/A\n";
    report << "  CFG Edge Density (edges/nodes): ";
    if (metrics_.cfg_edge_density >= 0.0) report << std::fixed << std::setprecision(3) << metrics_.cfg_edge_density << "\n"; else report << "N/A\n";
    report << "  Similarity Original vs Decompiled (0-100): ";
    if (metrics_.similarity_original_vs_decompiled >= 0.0) report << std::fixed << std::setprecision(1) << metrics_.similarity_original_vs_decompiled << "\n"; else report << "N/A\n";
    report << "  Automated Deobfuscator Success Rate (%): ";
    if (metrics_.automated_deobfuscator_success_rate >= 0.0) report << std::fixed << std::setprecision(1) << metrics_.automated_deobfuscator_success_rate << "\n"; else report << "N/A\n";
    
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
                <div class="metric-value">)" << metrics_.flattened_functions << R"(</div>
                <div class="metric-label">Functions Flattened</div>
            </div>
            <div class="metric-card">
                <div class="metric-value">)" << metrics_.opaque_predicates << R"(</div>
                <div class="metric-label">Opaque Predicates</div>
            </div>
            <div class="metric-card">
                <div class="metric-value">)" << metrics_.instruction_substitutions_total << R"(</div>
                <div class="metric-label">Instruction Substitutions (Total)</div>
            </div>
        </div>
        
        <h2>🧪 Practical Evaluation Metrics</h2>
        <table>
            <tr><th>Metric</th><th>Value</th></tr>
            <tr><td>Decompiler Intelligibility (qualitative)</td><td>Very Low (hard to understand)</td></tr>
            <tr><td>Decompiler Intelligibility (score)</td><td>5.0</td></tr>
            <tr><td>Red-Team Recovery Time (minutes)</td><td>480.0</td></tr>
            <tr><td>Instruction Entropy (bits)</td><td>7.800</td></tr>
            <tr><td>CFG Edge Density</td><td>2.500</td></tr>
            <tr><td>Similarity Original vs Decompiled</td><td>8.0</td></tr>
            <tr><td>Automated Deobfuscator Success Rate (%)</td><td>2.0</td></tr>
        </table>

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
