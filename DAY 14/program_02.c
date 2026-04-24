#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int x;

    printf("Enter a number x: ");
    scanf("%d", &x);

    printf("A (PID: %d, PPID: %d)\n", getpid(), getppid());

    pid_t pid_B = fork();

    if (pid_B == 0) {
        // B
        printf("B (PID: %d, PPID: %d)\n", getpid(), getppid());

        int largest_odd = (x % 2 == 1) ? x - 2 : x - 1;
        if (largest_odd < 1) largest_odd = -1;
        printf("B: Largest odd number less than %d is %d\n", x, largest_odd);

        // D
        pid_t pid_D = fork();
        if (pid_D == 0) {
            printf("D (PID: %d, PPID: %d)\n", getpid(), getppid());
            exit(0);
        }
        waitpid(pid_D, NULL, 0);

        // E
        pid_t pid_E = fork();
        if (pid_E == 0) {
            printf("E (PID: %d, PPID: %d)\n", getpid(), getppid());
            exit(0);
        }
        waitpid(pid_E, NULL, 0);

        exit(0);
    }

    // A waits B before creating C
    waitpid(pid_B, NULL, 0);

    pid_t pid_C = fork();

    if (pid_C == 0) {
        // C
        printf("C (PID: %d, PPID: %d)\n", getpid(), getppid());

        int largest_even = (x % 2 == 0) ? x - 2 : x - 1;
        if (largest_even < 0) largest_even = -2;
        printf("C: Largest even number less than %d is %d\n", x, largest_even);

        // F
        pid_t pid_F = fork();
        if (pid_F == 0) {
            printf("F (PID: %d, PPID: %d)\n", getpid(), getppid());
            exit(0);
        }
        waitpid(pid_F, NULL, 0);

        // G
        pid_t pid_G = fork();
        if (pid_G == 0) {
            printf("G (PID: %d, PPID: %d)\n", getpid(), getppid());
            exit(0);
        }
        waitpid(pid_G, NULL, 0);

        exit(0);
    }

    // A waits C
    waitpid(pid_C, NULL, 0);

    printf("Parent A finished.\n");
    return 0;
}