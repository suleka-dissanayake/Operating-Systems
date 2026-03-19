#include <stdio.h>
#include <unistd.h>

int main() {
    int n;
    printf("Enter a number: ");
    scanf("%d", &n);
    int c = fork();
    
    if (c == 0) printf("%d * 2 = %d\n", n, n * 2);
    else printf("%d / 2 = %d\n", n, n / 2);

    return 0;
}