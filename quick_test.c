#include <stdio.h>
#include <string.h>

int add(int a, int b) {
    return a + b;
}

int main() {
    char msg[] = "Hello World";
    int result = add(5, 10);
    
    printf("Message: %s\n", msg);
    printf("Sum: %d\n", result);
    
    if (strlen(msg) > 5) {
        printf("Long message!\n");
    }
    
    return 0;
}
