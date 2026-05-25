#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    int pipeA[2], pipeB[2], pipeC[2];
    int n, i;

    printf("[Parent] PID: %d - Enter number of integers: ", getpid());

    pid_t pid1 = fork();

    if (pid1 < 0) {
        perror("Fork failed");
        return 1;
    }

    // ----- CHILD PROCESS -----
    if (pid1 == 0) {

        pid_t pid2 = fork();

        // ----- GRANDCHILD PROCESS -----
        if (pid2 == 0) {

            int g_n, g_sum;

            read(pipeB[0], &g_n, sizeof(int));
            read(pipeB[0], &g_sum, sizeof(int));

            float average = (float)g_sum / g_n;

            printf("[Grandchild] PID: %d, PPID: %d - Calculated Average: %.2f\n",
                   getpid(), getppid(), average);

            // Send average back to Parent
            write(pipeC[1], &average, sizeof(float));

            exit(0);
        }

        // ----- CHILD PROCESS -----
        else {

            int received_n, num, sum = 0;

            // Read n
            read(pipeA[0], &received_n, sizeof(int));

            // Read numbers one by one
            for (i = 0; i < received_n; i++) {
                read(pipeA[0], &num, sizeof(int));
                sum += num;
            }

            printf("[Child] PID: %d, PPID: %d - Calculated Sum: %d\n",
                   getpid(), getppid(), sum);

            // Send n and sum to Grandchild
            write(pipeB[1], &received_n, sizeof(int));
            write(pipeB[1], &sum, sizeof(int));

            exit(0);
        }
    }

    // ----- PARENT PROCESS -----
    else {

        int num;

        printf("[Parent] PID: %d, PPID: %d - Enter %d integers:\n",
               getpid(), getppid(), n);

        // Send n first
        write(pipeA[1], &n, sizeof(int));

        // Send numbers one by one
        for (i = 0; i < n; i++) {
            scanf("%d", &num);
            write(pipeA[1], &num, sizeof(int));
        }

        printf("[Parent] Sent %d integers to Child via Pipe A.\n", n);

        // Receive average from Grandchild
        float average;

        read(pipeC[0], &average, sizeof(float));

        printf("[Parent] PID: %d - Received Final Average: %.2f\n",
               getpid(), average);
    }

    return 0;
}