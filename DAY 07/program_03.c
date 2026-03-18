#include <stdio.h>

int main() {
    int num;
    long long fact = 1;

    printf("Enter a number: ");

    if (scanf("%d", &num) != 1) {
        printf("Invalid input.\n");
        return 1;
    }

    if (num < 0) {
        printf("Error! Factorial of a negative number doesn't exist.\n");
    } else {
        for (int i = 1; i <= num; ++i) {
            fact *= i;
        }
        printf("Factorial of %d is %lld\n", num, fact);
    }

    return 0;
}