#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>

int main() {
    int pipeA[2], pipeB[2], pipeC[2];
    int n, i;

    // Initialize all pipes
    if (pipe(pipeA) == -1 || pipe(pipeB) == -1 || pipe(pipeC) == -1) {
        perror("Pipe failed");
        return 1;
    }

    printf("[Parent] PID: %d - Enter number of integers: ", getpid());
    if (scanf("%d", &n) <= 0 || n <= 0) {
        fprintf(stderr, "Invalid input.\n");
        return 1;
    }

    pid_t pid1 = fork();

    if (pid1 < 0) {
        perror("Fork failed");
        return 1;
    }

    if (pid1 > 0) { 
        // --- PARENT PROCESS ---
        int numbers[n];
        printf("[Parent] PID: %d, PPID: %d - Enter %d integers: ", getpid(), getppid(), n);
        for (i = 0; i < n; i++) {
            scanf("%d", &numbers[i]);
        }

        // Send N and numbers to Child
        write(pipeA[1], &n, sizeof(int));
        write(pipeA[1], numbers, sizeof(int) * n);
        printf("[Parent] Sent %d integers to Child via Pipe A.\n", n);

        // Wait for result from Grandchild via Pipe C
        float average;
        read(pipeC[0], &average, sizeof(float));
        printf("[Parent] PID: %d - Received Final Average from Grandchild: %.2f\n", getpid(), average);

        wait(NULL); // Sync: Wait for child to finish
    } else {
        // --- CHILD PROCESS ---
        pid_t pid2 = fork();

        if (pid2 < 0) {
            perror("Grandchild fork failed");
            exit(1);
        }

        if (pid2 > 0) {
            // Child logic
            int received_n, sum = 0;
            read(pipeA[0], &received_n, sizeof(int));
            int buffer[received_n];
            read(pipeA[0], buffer, sizeof(int) * received_n);

            for (i = 0; i < received_n; i++) sum += buffer[i];

            printf("[Child] PID: %d, PPID: %d - Calculated Sum: %d\n", getpid(), getppid(), sum);

            // Send sum and N to Grandchild
            write(pipeB[1], &received_n, sizeof(int));
            write(pipeB[1], &sum, sizeof(int));
            
            wait(NULL); // Sync: Wait for grandchild to finish
            exit(0);
        } else {
            // --- GRANDCHILD PROCESS ---
            int g_n, g_sum;
            read(pipeB[0], &g_n, sizeof(int));
            read(pipeB[0], &g_sum, sizeof(int));

            float average = (float)g_sum / g_n;
            printf("[Grandchild] PID: %d, PPID: %d - Calculated Average: %.2f\n", getpid(), getppid(), average);

            // Send back to Parent (Grandparent) via Pipe C
            write(pipeC[1], &average, sizeof(float));
            exit(0);
        }
    }

    return 0;
}
