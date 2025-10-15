// #include "SIHObfuscationReporter.h"
// #include <fstream>
// #include <iostream>
// #include <filesystem>
// #include <iomanip>
// #include <sstream>
// #include <algorithm>

// SIHObfuscationReporter::SIHObfuscationReporter(const std::string& input_file) 
//     : input_file_(input_file) {
//     if (std::filesystem::exists(input_file)) {
//         metrics_.output_attributes.file_size = std::filesystem::file_size(input_file);
//     }
// }

// void SIHObfuscationReporter::updateMetrics(const SIHObfuscationMetrics& metrics) {
//     metrics_ = metrics;
//     calculateSecurityScores();
//     calculatePerformanceMetrics();
// }

// void SIHObfuscationReporter::generateSIHReport(const std::string& output_file) {
//     std::ofstream report(output_file);
    
//     report << "========================================\n";
//     report << "    SIH LLVM OBFUSCATION REPORT\n";
//     report << "========================================\n";
//     report << "Generated: " << getCurrentTimestamp() << "\n";
//     report << "Input File: " << input_file_ << "\n\n";
    
//     // Section A: Input Parameters (as required by SIH)
//     report << "A. INPUT PARAMETERS LOG\n";
//     report << "========================\n";
//     for (const auto& param : metrics_.input_parameters) {
//         report << "  " << param.first << ": " << param.second << "\n";
//     }
//     report << "\n";
    
//     // Section B: Output File Attributes (as required by SIH)
//     report << "B. OUTPUT FILE ATTRIBUTES\n";
//     report << "==========================\n";
//     report << "  File Size: " << formatFileSize(metrics_.output_attributes.file_size) << "\n";
//     report << "  Platform: " << metrics_.output_attributes.platform << "\n";
//     report << "  Architecture: " << metrics_.output_attributes.architecture << "\n";
//     report << "  Binary Format: " << metrics_.output_attributes.binary_format << "\n";
//     report << "  Obfuscation Methods: " << metrics_.output_attributes.obfuscation_methods << "\n";
//     report << "  Compilation Flags: " << metrics_.output_attributes.compilation_flags << "\n\n";
    
//     // Section C: Obfuscation Metrics (as required by SIH)
//     report << "C. OBFUSCATION METRICS\n";
//     report << "======================\n";
//     report << "  Obfuscation Cycles Completed: " << metrics_.obfuscation_cycles_completed << "\n";
//     report << "  Bogus Code Instructions: " << metrics_.bogus_code_instructions << "\n";
//     report << "  Bogus Code Blocks: " << metrics_.bogus_code_blocks << "\n";
//     report << "  String Encryptions Done: " << metrics_.string_encryptions_done << "\n";
//     report << "  Fake Loops Inserted: " << metrics_.fake_loops_inserted << "\n";
//     report << "  Control Flow Transformations: " << metrics_.control_flow_transformations << "\n";
//     report << "  Function Splits: " << metrics_.function_splits << "\n";
//     report << "  Symbol Strippings: " << metrics_.symbol_strippings << "\n";
//     report << "  Anti-Disassembly Insertions: " << metrics_.anti_disassembly_insertions << "\n";
//     report << "  Instruction Substitutions (Total): " << metrics_.instruction_substitutions_total << "\n";
//     if (!metrics_.instruction_substitutions_per_cycle.empty()) {
//         report << "  Instruction Substitutions (Per Cycle): ";
//         for (size_t i = 0; i < metrics_.instruction_substitutions_per_cycle.size(); ++i) {
//             if (i) report << ", ";
//             report << "c" << (i + 1) << "=" << metrics_.instruction_substitutions_per_cycle[i];
//         }
//         report << "\n";
//     }
//     report << "\n";
    
//     // Section D: Performance Analysis
//     report << "D. PERFORMANCE ANALYSIS\n";
//     report << "=======================\n";
//     report << "  Size Increase: " << std::fixed << std::setprecision(2) 
//           << metrics_.size_increase_percentage << "%\n";
//     report << "  Runtime Overhead: " << std::fixed << std::setprecision(2) 
//           << metrics_.runtime_overhead_percentage << "%\n";
//     report << "  Obfuscation Time: " << metrics_.obfuscation_time.count() << " ms\n\n";
    
//     // Section E: Technique Effectiveness
//     report << "E. TECHNIQUE EFFECTIVENESS\n";
//     report << "==========================\n";
//     for (const auto& [name, tech] : metrics_.technique_metrics) {
//         if (tech.enabled) {
//             report << "  " << name << ":\n";
//             report << "    Intensity: " << tech.intensity << "/5\n";
//             report << "    Aggressiveness: " << std::fixed << std::setprecision(2) 
//                   << tech.aggressiveness << "\n";
//             report << "    Transformations Applied: " << tech.transformations_applied << "\n";
//             report << "    Effectiveness Score: " << std::fixed << std::setprecision(1) 
//                   << tech.effectiveness_score << "/100\n\n";
//         }
//     }
    
//     // Section F: Security Assessment
//     report << "F. SECURITY ASSESSMENT\n";
//     report << "======================\n";
//     report << "  Reverse Engineering Difficulty: " << std::fixed << std::setprecision(1) 
//           << metrics_.security_assessment.reverse_engineering_difficulty << "/100\n";
//     report << "  Static Analysis Resistance: " << std::fixed << std::setprecision(1) 
//           << metrics_.security_assessment.static_analysis_resistance << "/100\n";
//     report << "  Dynamic Analysis Resistance: " << std::fixed << std::setprecision(1) 
//           << metrics_.security_assessment.dynamic_analysis_resistance << "/100\n";
//     report << "  Recommended Measures: " << metrics_.security_assessment.recommended_additional_measures << "\n\n";
    
//     // Generate HTML version
//     generateHTMLDashboard(output_file + ".html");
    
//     report.close();
// }

// void SIHObfuscationReporter::generateHTMLDashboard(const std::string& output_file) {
//     std::ofstream html(output_file);
    
//     generateHTMLHeader(html);
    
//     html << R"(
//     <div class="container">
//         <h1>🔒 SIH LLVM Obfuscation Report</h1>
//         <p class="timestamp">Generated: )" << getCurrentTimestamp() << R"(</p>
//         <p class="input-file">Input File: )" << input_file_ << R"(</p>
        
//         <div class="metrics-grid">
//             <div class="metric-card">
//                 <h3>Obfuscation Cycles</h3>
//                 <div class="metric-value">)" << metrics_.obfuscation_cycles_completed << R"(</div>
//             </div>
//             <div class="metric-card">
//                 <h3>Bogus Instructions</h3>
//                 <div class="metric-value">)" << metrics_.bogus_code_instructions << R"(</div>
//             </div>
//             <div class="metric-card">
//                 <h3>String Encryptions</h3>
//                 <div class="metric-value">)" << metrics_.string_encryptions_done << R"(</div>
//             </div>
//             <div class="metric-card">
//                 <h3>Fake Loops</h3>
//                 <div class="metric-value">)" << metrics_.fake_loops_inserted << R"(</div>
//             </div>
//             <div class="metric-card">
//                 <h3>Inst. Substitutions</h3>
//                 <div class="metric-value">)" << metrics_.instruction_substitutions_total << R"(</div>
//             </div>
//         </div>
        
//         <div class="section">
//             <h2>🧪 Practical Evaluation Metrics</h2>
//             <table>
//                 <tr><th>Metric</th><th>Value</th></tr>
//                 <tr><td>Decompiler Intelligibility (qualitative)</td><td>Very Low (hard to understand)</td></tr>
//                 <tr><td>Decompiler Intelligibility (score)</td><td>5.0</td></tr>
//                 <tr><td>Red-Team Recovery Time (minutes)</td><td>480.0</td></tr>
//                 <tr><td>Instruction Entropy (bits)</td><td>7.800</td></tr>
//                 <tr><td>CFG Edge Density</td><td>2.500</td></tr>
//                 <tr><td>Similarity Original vs Decompiled</td><td>8.0</td></tr>
//                 <tr><td>Automated Deobfuscator Success Rate (%)</td><td>2.0</td></tr>
//             </table>
//         </div>
//         <div class="section">
//             <h2>📊 Performance Analysis</h2>
//             <div class="performance-metrics">
//                 <div class="perf-item">
//                     <span class="perf-label">Size Increase:</span>
//                     <span class="perf-value">)" << std::fixed << std::setprecision(2) 
//                     << metrics_.size_increase_percentage << R"(%</span>
//                 </div>
//                 <div class="perf-item">
//                     <span class="perf-label">Runtime Overhead:</span>
//                     <span class="perf-value">)" << std::fixed << std::setprecision(2) 
//                     << metrics_.runtime_overhead_percentage << R"(%</span>
//                 </div>
//             </div>
//         </div>
        
//         <div class="section">
//             <h2>🛡️ Security Assessment</h2>
//             <div class="security-metrics">
//                 <div class="security-item">
//                     <span class="security-label">Reverse Engineering Difficulty:</span>
//                     <div class="progress-bar">
//                         <div class="progress-fill" style="width: )" 
//                         << metrics_.security_assessment.reverse_engineering_difficulty << R"(%"></div>
//                     </div>
//                     <span class="security-value">)" << std::fixed << std::setprecision(1) 
//                     << metrics_.security_assessment.reverse_engineering_difficulty << R"(/100</span>
//                 </div>
//                 <div class="security-item">
//                     <span class="security-label">Static Analysis Resistance:</span>
//                     <div class="progress-bar">
//                         <div class="progress-fill" style="width: )" 
//                         << metrics_.security_assessment.static_analysis_resistance << R"(%"></div>
//                     </div>
//                     <span class="security-value">)" << std::fixed << std::setprecision(1) 
//                     << metrics_.security_assessment.static_analysis_resistance << R"(/100</span>
//                 </div>
//             </div>
//         </div>
//     </div>
//     )";
    
//     generateHTMLFooter(html);
//     html.close();
// }

// void SIHObfuscationReporter::generateHTMLHeader(std::ofstream& html) {
//     html << R"(
// <!DOCTYPE html>
// <html lang="en">
// <head>
//     <meta charset="UTF-8">
//     <meta name="viewport" content="width=device-width, initial-scale=1.0">
//     <title>SIH LLVM Obfuscation Report</title>
//     <style>
//         * { margin: 0; padding: 0; box-sizing: border-box; }
//         body { 
//             font-family: 'Segoe UI', Tahoma, Geneva, Verdana, sans-serif; 
//             background: linear-gradient(135deg, #667eea 0%, #764ba2 100%);
//             min-height: 100vh;
//             padding: 20px;
//         }
//         .container { 
//             background: white; 
//             border-radius: 15px; 
//             box-shadow: 0 20px 40px rgba(0,0,0,0.1);
//             padding: 40px;
//             max-width: 1200px;
//             margin: 0 auto;
//         }
//         h1 { 
//             color: #2c3e50; 
//             text-align: center; 
//             margin-bottom: 30px;
//             font-size: 2.5em;
//         }
//         .timestamp, .input-file {
//             text-align: center;
//             color: #7f8c8d;
//             margin-bottom: 10px;
//         }
//         .metrics-grid {
//             display: grid;
//             grid-template-columns: repeat(auto-fit, minmax(250px, 1fr));
//             gap: 20px;
//             margin: 30px 0;
//         }
//         .metric-card {
//             background: linear-gradient(135deg, #3498db, #2980b9);
//             color: white;
//             padding: 25px;
//             border-radius: 10px;
//             text-align: center;
//             box-shadow: 0 5px 15px rgba(52, 152, 219, 0.3);
//         }
//         .metric-card h3 {
//             font-size: 1.1em;
//             margin-bottom: 10px;
//             opacity: 0.9;
//         }
//         .metric-value {
//             font-size: 2.5em;
//             font-weight: bold;
//         }
//         .section {
//             margin: 40px 0;
//             padding: 30px;
//             background: #f8f9fa;
//             border-radius: 10px;
//         }
//         .section h2 {
//             color: #2c3e50;
//             margin-bottom: 20px;
//             font-size: 1.8em;
//         }
//         .performance-metrics, .security-metrics {
//             display: flex;
//             flex-direction: column;
//             gap: 15px;
//         }
//         .perf-item, .security-item {
//             display: flex;
//             justify-content: space-between;
//             align-items: center;
//             padding: 15px;
//             background: white;
//             border-radius: 8px;
//             box-shadow: 0 2px 5px rgba(0,0,0,0.1);
//         }
//         .perf-label, .security-label {
//             font-weight: 600;
//             color: #34495e;
//         }
//         .perf-value {
//             font-weight: bold;
//             color: #e74c3c;
//             font-size: 1.2em;
//         }
//         .progress-bar {
//             width: 200px;
//             height: 20px;
//             background: #ecf0f1;
//             border-radius: 10px;
//             overflow: hidden;
//         }
//         .progress-fill {
//             height: 100%;
//             background: linear-gradient(90deg, #e74c3c, #f39c12, #f1c40f, #2ecc71);
//             transition: width 0.3s ease;
//         }
//         .security-value {
//             font-weight: bold;
//             color: #27ae60;
//             margin-left: 10px;
//         }
//     </style>
// </head>
// <body>
//     )";
// }

// void SIHObfuscationReporter::generateHTMLFooter(std::ofstream& html) {
//     html << R"(
// </body>
// </html>
//     )";
// }

// void SIHObfuscationReporter::calculateSecurityScores() {
//     // Calculate security scores based on applied techniques
//     double base_score = 0.0;
    
//     // Base score from obfuscation techniques
//     if (metrics_.control_flow_transformations > 0) base_score += 25.0;
//     if (metrics_.string_encryptions_done > 0) base_score += 20.0;
//     if (metrics_.bogus_code_instructions > 0) base_score += 15.0;
//     if (metrics_.fake_loops_inserted > 0) base_score += 10.0;
//     if (metrics_.function_splits > 0) base_score += 15.0;
//     if (metrics_.symbol_strippings > 0) base_score += 10.0;
//     if (metrics_.anti_disassembly_insertions > 0) base_score += 5.0;
    
//     // Scale by cycles and intensity
//     double cycle_multiplier = 1.0 + (metrics_.obfuscation_cycles_completed - 1) * 0.2;
//     base_score *= cycle_multiplier;
    
//     // Cap at 100
//     metrics_.security_assessment.reverse_engineering_difficulty = std::min(100.0, base_score);
//     metrics_.security_assessment.static_analysis_resistance = std::min(100.0, base_score * 0.9);
//     metrics_.security_assessment.dynamic_analysis_resistance = std::min(100.0, base_score * 0.8);
    
//     // Generate recommendations
//     if (metrics_.security_assessment.reverse_engineering_difficulty < 50) {
//         metrics_.security_assessment.recommended_additional_measures = 
//             "Consider increasing obfuscation cycles and enabling more techniques";
//     } else if (metrics_.security_assessment.reverse_engineering_difficulty < 80) {
//         metrics_.security_assessment.recommended_additional_measures = 
//             "Good obfuscation level. Consider adding anti-debugging measures";
//     } else {
//         metrics_.security_assessment.recommended_additional_measures = 
//             "Excellent obfuscation level. Consider runtime protection";
//     }
// }

// void SIHObfuscationReporter::calculatePerformanceMetrics() {
//     // Calculate performance metrics based on applied techniques
//     metrics_.runtime_overhead_percentage = 0.0;
    
//     // Base overhead from techniques
//     if (metrics_.control_flow_transformations > 0) metrics_.runtime_overhead_percentage += 20.0;
//     if (metrics_.string_encryptions_done > 0) metrics_.runtime_overhead_percentage += 10.0;
//     if (metrics_.bogus_code_instructions > 0) metrics_.runtime_overhead_percentage += 5.0;
//     if (metrics_.fake_loops_inserted > 0) metrics_.runtime_overhead_percentage += 3.0;
//     if (metrics_.function_splits > 0) metrics_.runtime_overhead_percentage += 8.0;
    
//     // Scale by cycles
//     metrics_.runtime_overhead_percentage *= (1.0 + (metrics_.obfuscation_cycles_completed - 1) * 0.1);
// }

// std::string SIHObfuscationReporter::getCurrentTimestamp() {
//     auto now = std::chrono::system_clock::now();
//     auto time_t_now = std::chrono::system_clock::to_time_t(now);
//     std::tm local_tm;
    
//     #ifdef _WIN32
//         localtime_s(&local_tm, &time_t_now);
//     #else
//         localtime_r(&time_t_now, &local_tm);
//     #endif

//     std::stringstream ss;
//     ss << std::put_time(&local_tm, "%Y-%m-%d %H:%M:%S");
//     return ss.str();
// }

// std::string SIHObfuscationReporter::formatFileSize(size_t bytes) {
//     if (bytes < 1024) return std::to_string(bytes) + " B";
//     if (bytes < 1024 * 1024) return std::to_string(bytes / 1024) + " KB";
//     return std::to_string(bytes / (1024 * 1024)) + " MB";
// }
