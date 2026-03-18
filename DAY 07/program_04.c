#include <stdio.h>

int main() {
    int n, a = 0, b = 1, i = 0;
    printf("Enter number of terms: ");
    scanf("%d", &n);

    while (i < n) {
        printf("%d ", a);
        b = a + b; 
        a = b - a; 
        i++;
    }

    return 0;
}