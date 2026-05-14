#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    int x;
    int pipe_B[2], pipe_C[2];

    pipe(pipe_B);
    pipe(pipe_C);

    printf("Enter a number x: ");
    scanf("%d", &x);

    printf("A (PID: %d, PPID: %d)\n", getpid(), getppid());

    pid_t pid_B = fork();

    if (pid_B == 0) {

        // Child B
        close(pipe_B[0]);

        printf("B (PID: %d, PPID: %d)\n", getpid(), getppid());

        int largest_odd = (x % 2 == 1) ? x - 2 : x - 1;

        if (largest_odd < 1)
            largest_odd = -1;

        printf("B: Largest odd number less than %d is %d\n", x, largest_odd);

        // D
        if (fork() == 0) {
            printf("D (PID: %d, PPID: %d)\n", getpid(), getppid());
            exit(0);
        }

        // E
        if (fork() == 0) {
            printf("E (PID: %d, PPID: %d)\n", getpid(), getppid());
            exit(0);
        }

        // signal parent A
        write(pipe_B[1], "x", 1);

        close(pipe_B[1]);

        exit(0);
    }

    pid_t pid_C = fork();

    if (pid_C == 0) {

        // Child C
        close(pipe_C[0]);

        printf("C (PID: %d, PPID: %d)\n", getpid(), getppid());

        int largest_even = (x % 2 == 0) ? x - 2 : x - 1;

        if (largest_even < 0)
            largest_even = -2;

        printf("C: Largest even number less than %d is %d\n", x, largest_even);

        // F
        if (fork() == 0) {
            printf("F (PID: %d, PPID: %d)\n", getpid(), getppid());
            exit(0);
        }

        // G
        if (fork() == 0) {
            printf("G (PID: %d, PPID: %d)\n", getpid(), getppid());
            exit(0);
        }

        // signal parent A
        write(pipe_C[1], "x", 1);

        close(pipe_C[1]);

        exit(0);
    }

    // Parent A waits using blocking read()
    close(pipe_B[1]);
    close(pipe_C[1]);

    char temp;

    read(pipe_B[0], &temp, 1);
    read(pipe_C[0], &temp, 1);

    printf("Parent A finished.\n");

    return 0;
}