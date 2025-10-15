#pragma once

#include <string>
#include <vector>
#include <map>
#include <cstdint>
#include <chrono>

// Enhanced metrics structure for SIH requirements
struct SIHObfuscationMetrics {
    // Input parameters (as required by SIH)
    std::map<std::string, std::string> input_parameters;
    
    // Output file attributes (as required by SIH)
    struct OutputFileAttributes {
        size_t file_size = 0;
        std::string platform = "";
        std::string architecture = "";
        std::string obfuscation_methods = "";
        std::string binary_format = "";  // PE/ELF
        std::string compilation_flags = "";
    } output_attributes;
    
    // Obfuscation metrics (as required by SIH)
    int obfuscation_cycles_completed = 0;
    int bogus_code_instructions = 0;
    int bogus_code_blocks = 0;
    int string_encryptions_done = 0;
    int fake_loops_inserted = 0;
    int control_flow_transformations = 0;
    int function_splits = 0;
    int symbol_strippings = 0;
    int anti_disassembly_insertions = 0;

    // Instruction substitution metrics
    std::vector<int> instruction_substitutions_per_cycle; // per-cycle counts
    int instruction_substitutions_total = 0;

    // Practical evaluation metrics
    std::string decompiler_intelligibility_qualitative;
    double decompiler_intelligibility_score = -1.0;
    double red_team_recovery_time_minutes = -1.0;
    double instruction_entropy = -1.0;
    double cfg_edge_density = -1.0;
    double similarity_original_vs_decompiled = -1.0;
    double automated_deobfuscator_success_rate = -1.0;
    
    // Performance metrics
    double size_increase_percentage = 0.0;
    double runtime_overhead_percentage = 0.0;
    std::chrono::milliseconds obfuscation_time;
    
    // Technique-specific metrics
    struct TechniqueMetrics {
        bool enabled = false;
        int intensity = 0;
        double aggressiveness = 0.0;
        int transformations_applied = 0;
        double effectiveness_score = 0.0;
    };
    
    std::map<std::string, TechniqueMetrics> technique_metrics;
    
    // Security assessment
    struct SecurityAssessment {
        double reverse_engineering_difficulty = 0.0;  // 0-100 scale
        double static_analysis_resistance = 0.0;       // 0-100 scale
        double dynamic_analysis_resistance = 0.0;       // 0-100 scale
        std::string recommended_additional_measures = "";
    } security_assessment;
};

// Enhanced reporter class for SIH requirements
class SIHObfuscationReporter {
public:
    SIHObfuscationReporter(const std::string& input_file);
    
    // Core reporting methods
    void updateMetrics(const SIHObfuscationMetrics& metrics);
    void generateSIHReport(const std::string& output_file);
    void generateDetailedAnalysis(const std::string& output_file);
    
    // SIH-specific report sections
    void generateInputParametersLog(const std::string& output_file);
    void generateOutputFileAttributes(const std::string& output_file);
    void generateObfuscationMetrics(const std::string& output_file);
    void generateSecurityAssessment(const std::string& output_file);
    void generatePerformanceAnalysis(const std::string& output_file);
    
    // HTML dashboard generation
    void generateHTMLDashboard(const std::string& output_file);
    void generateInteractiveReport(const std::string& output_file);
    
private:
    std::string input_file_;
    SIHObfuscationMetrics metrics_;
    
    // Helper methods
    void calculateSecurityScores();
    void calculatePerformanceMetrics();
    std::string getCurrentTimestamp();
    std::string formatFileSize(size_t bytes);
    std::string generateTechniqueSummary();
    std::string generateSecurityRecommendations();
    
    // HTML generation helpers
    void generateHTMLHeader(std::ofstream& html);
    void generateHTMLFooter(std::ofstream& html);
    void generateHTMLMetricsSection(std::ofstream& html);
    void generateHTMLSecuritySection(std::ofstream& html);
    void generateHTMLPerformanceSection(std::ofstream& html);
};
