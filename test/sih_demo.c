#include <stdio.h>
#include <string.h>
#include <stdlib.h>

// Authentication function for SIH demo
int authenticate_user(char* username, char* password) {
    char* valid_users[] = {"admin", "user", "guest"};
    char* valid_passwords[] = {"admin123", "userpass", "guest"};
    
    for (int i = 0; i < 3; i++) {
        if (strcmp(username, valid_users[i]) == 0 && 
            strcmp(password, valid_passwords[i]) == 0) {
            return 1; // Authentication successful
        }
    }
    return 0; // Authentication failed
}

// Secret algorithm for SIH demo
int calculate_secret_value(int input) {
    int result = input;
    
    // Complex computation
    for (int i = 0; i < 10; i++) {
        if (result % 2 == 0) {
            result = result / 2;
        } else {
            result = result * 3 + 1;
        }
    }
    
    return result;
}

int main(int argc, char* argv[]) {
    printf("=== SIH LLVM Obfuscator Demo ===\n");
    
    if (argc < 3) {
        printf("Usage: %s <username> <password>\n", argv[0]);
        return 1;
    }
    
    char* username = argv[1];
    char* password = argv[2];
    
    printf("Authenticating user: %s\n", username);
    
    if (authenticate_user(username, password)) {
        printf("✅ Authentication successful!\n");
        
        int secret_value = calculate_secret_value(42);
        printf("🔐 Secret value: %d\n", secret_value);
        
        printf("🎉 Access granted to secure system!\n");
    } else {
        printf("❌ Authentication failed!\n");
        printf("🚫 Access denied!\n");
    }
    
    return 0;
}
