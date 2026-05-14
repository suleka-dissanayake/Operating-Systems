#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {

    int x;

    int pipe_B[2], pipe_C[2];
    int pipe_D[2], pipe_E[2];
    int pipe_F[2], pipe_G[2];

    char temp;

    pipe(pipe_B);
    pipe(pipe_C);
    pipe(pipe_D);
    pipe(pipe_E);
    pipe(pipe_F);
    pipe(pipe_G);

    printf("Enter a number x: ");
    scanf("%d", &x);

    printf("A (PID: %d, PPID: %d)\n", getpid(), getppid());

    pid_t pid_B = fork();

    if (pid_B == 0) {

        close(pipe_B[0]);

        printf("B (PID: %d, PPID: %d)\n", getpid(), getppid());

        int largest_odd = (x % 2 == 1) ? x - 2 : x - 1;

        if (largest_odd < 1)
            largest_odd = -1;

        printf("B: Largest odd number less than %d is %d\n", x, largest_odd);

        // D
        if (fork() == 0) {

            close(pipe_D[0]);

            printf("D (PID: %d, PPID: %d)\n", getpid(), getppid());

            write(pipe_D[1], "x", 1);

            close(pipe_D[1]);

            exit(0);
        }

        read(pipe_D[0], &temp, 1);

        // E
        if (fork() == 0) {

            close(pipe_E[0]);

            printf("E (PID: %d, PPID: %d)\n", getpid(), getppid());

            write(pipe_E[1], "x", 1);

            close(pipe_E[1]);

            exit(0);
        }

        read(pipe_E[0], &temp, 1);

        write(pipe_B[1], "x", 1);

        close(pipe_B[1]);

        exit(0);
    }

    // A waits for B using pipe
    read(pipe_B[0], &temp, 1);

    pid_t pid_C = fork();

    if (pid_C == 0) {

        close(pipe_C[0]);

        printf("C (PID: %d, PPID: %d)\n", getpid(), getppid());

        int largest_even = (x % 2 == 0) ? x - 2 : x - 1;

        if (largest_even < 0)
            largest_even = -2;

        printf("C: Largest even number less than %d is %d\n", x, largest_even);

        // F
        if (fork() == 0) {

            close(pipe_F[0]);

            printf("F (PID: %d, PPID: %d)\n", getpid(), getppid());

            write(pipe_F[1], "x", 1);

            close(pipe_F[1]);

            exit(0);
        }

        read(pipe_F[0], &temp, 1);

        // G
        if (fork() == 0) {

            close(pipe_G[0]);

            printf("G (PID: %d, PPID: %d)\n", getpid(), getppid());

            write(pipe_G[1], "x", 1);

            close(pipe_G[1]);

            exit(0);
        }

        read(pipe_G[0], &temp, 1);

        write(pipe_C[1], "x", 1);

        close(pipe_C[1]);

        exit(0);
    }

    // A waits for C using pipe
    read(pipe_C[0], &temp, 1);

    printf("Parent A finished.\n");

    return 0;
}