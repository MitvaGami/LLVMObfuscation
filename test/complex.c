#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

// Function with multiple branches for CF flattening
int calculate_score(int a, int b, int c) {
    int result = 0;
    
    if (a > b) {
        if (b > c) {
            result = a * b + c;
        } else {
            result = a + b * c;
        }
    } else {
        if (a > c) {
            result = b * c - a;
        } else {
            result = (a + b + c) / 3;
        }
    }
    
    for (int i = 0; i < 3; i++) {
        result += i * 2;
    }
    
    return result;
}

// Function with string operations
void process_strings() {
    char buffer[100];
    char *messages[] = {
        "Confidential Data",
        "Secret Algorithm", 
        "Protected Information",
        "Classified Content"
    };
    
    printf("Processing secure data...\n");
    
    for (int i = 0; i < 4; i++) {
        strcpy(buffer, messages[i]);
        printf("Message %d: %s (length: %lu)\n", i+1, buffer, strlen(buffer));
    }
}

// Recursive function for splitting
long factorial(int n) {
    if (n <= 1) {
        return 1;
    }
    
    long temp = factorial(n - 1);
    return n * temp;
}

// Function with complex control flow
int complex_algorithm(int input) {
    int state = 0;
    int counter = 0;
    
    while (counter < 10) {
        switch (state) {
            case 0:
                if (input % 2 == 0) {
                    state = 1;
                    input /= 2;
                } else {
                    state = 2;
                    input = input * 3 + 1;
                }
                break;
                
            case 1:
                if (input < 10) {
                    state = 3;
                } else {
                    state = 0;
                    input -= 5;
                }
                break;
                
            case 2:
                if (input > 100) {
                    state = 0;
                    input /= 4;
                } else {
                    state = 1;
                    input += 7;
                }
                break;
                
            case 3:
                return input + counter;
                
            default:
                state = 0;
                break;
        }
        counter++;
    }
    
    return input;
}

int main(int argc, char *argv[]) {
    printf("=== Advanced LLVM Obfuscator Test Program ===\n");
    
    // Test different functions
    int score = calculate_score(15, 10, 25);
    printf("Calculated score: %d\n", score);
    
    process_strings();
    
    long fact = factorial(8);
    printf("Factorial of 8: %ld\n", fact);
    
    srand(time(NULL));
    int random_input = rand() % 100 + 1;
    int algorithm_result = complex_algorithm(random_input);
    printf("Complex algorithm result for input %d: %d\n", random_input, algorithm_result);
    
    // Test with command line arguments
    if (argc > 1) {
        printf("Command line argument received: %s\n", argv[1]);
        int arg_value = atoi(argv[1]);
        if (arg_value > 0) {
            printf("Processing argument value: %d\n", arg_value);
            int processed = complex_algorithm(arg_value);
            printf("Processed result: %d\n", processed);
        }
    }
    
    printf("Program execution completed.\n");
    return 0;
}
