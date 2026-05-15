#include <stdio.h>

int main(void) {
    for (int i = 100; i <= 999; i++) {
        int n1 = i / 100;
        int n2 = (i / 10) % 10;
        int n3 = i % 10;
        if (i == n1*n1*n1 + n2*n2*n2 + n3*n3*n3) {
            printf("%d is an armstrong number!\n", i);
        }
    }
    return 0;
}