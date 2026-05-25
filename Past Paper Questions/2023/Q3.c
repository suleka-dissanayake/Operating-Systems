#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    int pipeA[2], pipeB[2], pipeC[2];
    int child_pid, grandchild_pid;

    if (pipe(pipeA) == -1 || pipe(pipeB) == -1 || pipe(pipeC) == -1) {
        perror("Error: Pipe creation failed");
        exit(1);
    }

    child_pid = fork();

    // ==========================================
    // CHILD PROCESS
    // ==========================================
    if (child_pid == 0) {

        grandchild_pid = fork();

        if (grandchild_pid < 0) {
            perror("Error: Fork failed");
            exit(1);
        }

        // ==========================================
        // GRANDCHILD PROCESS
        // ==========================================
        if (grandchild_pid == 0) {

            close(pipeA[0]);
            close(pipeA[1]);

            close(pipeB[1]);

            close(pipeC[0]);

            int n, sum;

            read(pipeB[0], &n, sizeof(int));
            read(pipeB[0], &sum, sizeof(int));

            close(pipeB[0]);

            float average = (float)sum / n;

            printf("[Grandchild] PID: %d, PPID: %d, "
                   "Activity: Calculated average, Value: %.2f\n",
                   getpid(), getppid(), average);

            write(pipeC[1], &average, sizeof(float));

            close(pipeC[1]);
        }

        // ==========================================
        // CHILD PROCESS
        // ==========================================
        else {

            close(pipeA[1]);

            close(pipeB[0]);

            close(pipeC[0]);
            close(pipeC[1]);

            int n;

            read(pipeA[0], &n, sizeof(int));

            // Fixed-size array instead of malloc
            int arr[100];

            read(pipeA[0], arr, n * sizeof(int));

            close(pipeA[0]);

            int sum = 0;

            for (int i = 0; i < n; i++) {
                sum += arr[i];
            }

            printf("[Child] PID: %d, PPID: %d, "
                   "Activity: Calculated sum, Value: %d\n",
                   getpid(), getppid(), sum);

            write(pipeB[1], &n, sizeof(int));
            write(pipeB[1], &sum, sizeof(int));

            close(pipeB[1]);
        }
    }

    // ==========================================
    // PARENT PROCESS
    // ==========================================
    else {

        close(pipeA[0]);

        close(pipeB[0]);
        close(pipeB[1]);

        close(pipeC[1]);

        int n;

        printf("Enter the number of integers (N): ");
        scanf("%d", &n);

        // Fixed-size array instead of malloc
        int arr[100];

        printf("Enter %d integers:\n", n);

        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        printf("[Parent] PID: %d, PPID: %d, "
               "Activity: Sending N and array to Child\n",
               getpid(), getppid());

        write(pipeA[1], &n, sizeof(int));
        write(pipeA[1], arr, n * sizeof(int));

        close(pipeA[1]);

        float average;

        read(pipeC[0], &average, sizeof(float));

        printf("[Parent] PID: %d, PPID: %d, "
               "Activity: Received average, Value: %.2f\n",
               getpid(), getppid(), average);

        close(pipeC[0]);
    }

    return 0;
}