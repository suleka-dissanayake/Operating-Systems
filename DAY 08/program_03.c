#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int n1, n2;
    int pipe1[2], pipe2[2], pipe3[2], pipe4[2];
    char temp;

    pipe(pipe1);
    pipe(pipe2);
    pipe(pipe3);
    pipe(pipe4);

    printf("Enter two numbers: ");
    scanf("%d %d", &n1, &n2);

    // Addition
    if (fork() == 0) {
        close(pipe1[0]);
        printf("Addition: %d\n", n1 + n2);
        write(pipe1[1], "x", 1);
        close(pipe1[1]);
        exit(0);
    }

    // Subtraction
    if (fork() == 0) {

        close(pipe2[0]);

        printf("Subtraction: %d\n", n1 - n2);

        write(pipe2[1], "x", 1);

        close(pipe2[1]);

        exit(0);
    }

    // Multiplication
    if (fork() == 0) {

        close(pipe3[0]);

        printf("Multiplication: %d\n", n1 * n2);

        write(pipe3[1], "x", 1);

        close(pipe3[1]);

        exit(0);
    }

    // Division
    if (fork() == 0) {

        close(pipe4[0]);

        printf("Division: %d\n", n1 / n2);

        write(pipe4[1], "x", 1);

        close(pipe4[1]);

        exit(0);
    }

    // Parent waits using pipes

    read(pipe1[0], &temp, 1);
    read(pipe2[0], &temp, 1);
    read(pipe3[0], &temp, 1);
    read(pipe4[0], &temp, 1);

    printf("All operations complete.\n");

    return 0;
}