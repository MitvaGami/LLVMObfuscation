#pragma once // Prevents multiple inclusions of this header

#include <string>
#include <vector>
#include <map>
#include <cstdint> // For size_t

// Define the ObfuscationMetrics struct that was missing
struct ObfuscationMetrics {
    // Input parameters
    std::map<std::string, std::string> parameters;

    // Obfuscation counts
    int obfuscation_cycles = 0;
    int bogus_instructions = 0;
    int encrypted_strings = 0;
    int fake_loops = 0; // from bogus control flow
    int flattened_functions = 0;
    int opaque_predicates = 0;

    // Instruction substitution metrics
    std::vector<int> instruction_substitutions_per_cycle; // length == obfuscation_cycles (if known)
    int instruction_substitutions_total = 0;

    // File size metrics
    size_t original_size = 0;
    size_t obfuscated_size = 0;

    // Performance metrics
    double execution_time_overhead = 0.0;

    // Practical evaluation metrics (optional; computed or provided by caller)
    // Decompiler intelligibility
    std::string decompiler_intelligibility_qualitative; // e.g., "Low/Medium/High"
    double decompiler_intelligibility_score = -1.0; // 0-100, -1 if unknown
    // Red-team recovery time (minutes)
    double red_team_recovery_time_minutes = -1.0; // -1 if unknown
    // Entropy of instruction frequencies (Shannon entropy, bits)
    double instruction_entropy = -1.0; // -1 if unknown
    // CFG edge density (edges / nodes)
    double cfg_edge_density = -1.0; // -1 if unknown
    // Similarity score between original and decompiled outputs (0-100)
    double similarity_original_vs_decompiled = -1.0; // -1 if unknown
    // Success rate of automated deobfuscators (0-100%)
    double automated_deobfuscator_success_rate = -1.0; // -1 if unknown
};

// Declare the ObfuscationReporter class
class ObfuscationReporter {
public:
    // Constructor
    ObfuscationReporter(const std::string& input_file);

    // Public methods
    void updateMetrics(const ObfuscationMetrics& metrics);
    void generateReport(const std::string& output_file);

private:
    // Private member variables
    std::string input_file_;
    ObfuscationMetrics metrics_;

    // Private helper methods
    void calculateSizeIncrease();
    std::string getCurrentTimestamp();
    void generateHTMLReport(const std::string& output_file);
};
