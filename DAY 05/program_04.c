#include <stdio.h>
#include <unistd.h>

int main() {
    printf("Hi\n");
    fork();
    printf("Hello world\n")
}