#include <stdio.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int n1, n2;
    printf("Enter two numbers: ");
    scanf("%d %d", &n1, &n2);

    if (fork() == 0) {
        printf("Addition: %d\n", n1 + n2);
    } else if (fork() == 0) {
        printf("Subtraction: %d\n", n1 - n2);
    } else if (fork() == 0) {
        printf("Multiplication: %d\n", n1 * n2);
    } else if (fork() == 0) {
        printf("Division: %d\n", n1 / n2);
    } else {
        while(wait(NULL) > 0); 
        printf("All operations complete.\n");
    }

    return 0;
}