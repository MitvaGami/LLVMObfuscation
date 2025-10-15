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
    int fake_loops = 0;
    int flattened_functions = 0;
    int opaque_predicates = 0;
    int split_functions = 0;

    // File size metrics
    size_t original_size = 0;
    size_t obfuscated_size = 0;

    // Performance metrics
    double execution_time_overhead = 0.0;
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
