#include <stdio.h>

int main() {
    int a, b;
    char op;

    printf("Enter expression (e.g., 1 + 2): ");
    scanf("%d %c %d", &a, &op, &b);

    if (op == '+') {
        printf("Result: %d\n", a + b);
    }
    else if (op == '-') {
        printf("Result: %d\n", a - b);
    }
    else if (op == '*') {
        printf("Result: %d\n", a * b);
    }
    else if (op == '/') {
        if (b != 0)
            printf("Result: %d\n", a / b);
        else
            printf("Error: Division by zero\n");
    }
    else {
        printf("Invalid operator\n");
    }

    return 0;
}