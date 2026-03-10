#include <stdio.h>
#include <unistd.h>

int main() {
    int f = fork();
    printf("\nHello World\n");
    printf("Fork returns %d \n", f);
    return 0;
}