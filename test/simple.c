#include <stdio.h>
#include <string.h>

int fibonacci(int n) {
    if (n <= 1) return n;
    return fibonacci(n-1) + fibonacci(n-2);
}

int main() {
    char secret[] = "Hello World!";
    int result = fibonacci(10);
    
    printf("Secret: %s\n", secret);
    printf("Fibonacci(10) = %d\n", result);
    
    if (strlen(secret) > 5) {
        printf("Long secret detected!\n");
    }
    
    return 0;
}
