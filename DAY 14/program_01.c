#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>

int main() {
    int x;

    // Parent A reads input
    printf("Enter a number x: ");
    scanf("%d", &x);

    printf("A (PID: %d, PPID: %d)\n", getpid(), getppid());

    pid_t pid_B = fork();

    if (pid_B == 0) {
        // Child B: largest odd number < x
        printf("B (PID: %d, PPID: %d)\n", getpid(), getppid());
        
        int largest_odd = (x % 2 == 1) ? x - 2 : x - 1;
        if (largest_odd < 1) largest_odd = -1; // Handle edge case
        printf("B: Largest odd number less than %d is %d\n", x, largest_odd);

        // B creates its children D and E
        pid_t pid_D = fork();
        if (pid_D == 0) {
            printf("D (PID: %d, PPID: %d)\n", getpid(), getppid());
            exit(0);
        }

        pid_t pid_E = fork();
        if (pid_E == 0) {
            printf("E (PID: %d, PPID: %d)\n", getpid(), getppid());
            exit(0);
        }

        // B waits for D and E
        wait(NULL);
        wait(NULL);
        exit(0);
    }
    else if (pid_B > 0) {
        pid_t pid_C = fork();

        if (pid_C == 0) {
            // Child C: largest even number < x
            printf("C (PID: %d, PPID: %d)\n", getpid(), getppid());
            
            int largest_even = (x % 2 == 0) ? x - 2 : x - 1;
            if (largest_even < 0) largest_even = -2; // Handle edge case
            printf("C: Largest even number less than %d is %d\n", x, largest_even);

            // C creates its children F and G
            pid_t pid_F = fork();
            if (pid_F == 0) {
                printf("F (PID: %d, PPID: %d)\n", getpid(), getppid());
                exit(0);
            }

            pid_t pid_G = fork();
            if (pid_G == 0) {
                printf("G (PID: %d, PPID: %d)\n", getpid(), getppid());
                exit(0);
            }

            // C waits for F and G
            wait(NULL);
            wait(NULL);
            exit(0);
        }
    }

    // Parent A waits for B and C
    wait(NULL);
    wait(NULL);
    printf("Parent A finished.\n");
    return 0;
}