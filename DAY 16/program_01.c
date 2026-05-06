#include <stdio.h>

int main() {
    for (int num = 100; num <= 999; num++) {
        int n1 = num / 100;
        int n2 = (num / 10) % 10;
        int n3 = num % 10;

        if ((n1 * n1 * n1) + (n2 * n2 * n2) + (n3 * n3 * n3) == num) {
            printf("%d is an Armstrong number!\n", num);
        }
    }
    return 0;
}