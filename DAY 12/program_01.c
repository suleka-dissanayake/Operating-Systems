#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int index = 372;  // Number to process

    // Pipes:
    // AB: A → B
    // BA: B → A
    // AC: A → C
    // CA: C → A
    int pipeAB[2], pipeBA[2];
    int pipeAC[2], pipeCA[2];

    // Create pipes
    pipe(pipeAB);
    pipe(pipeBA);
    pipe(pipeAC);   // FIXED (was PPID)
    pipe(pipeCA);

    // Create process B
    int B = fork();

    if (B == 0) {
        // CHILD PROCESS B

        close(pipeAB[1]); // Close write end (B only reads from A)
        close(pipeBA[0]); // Close read end (B only writes to A)

        int num;
        read(pipeAB[0], &num, sizeof(num)); // Read number from A
        close(pipeAB[0]);

        printf("Process B (PID - %d, PPID - %d)\n", getpid(), getppid());

        // Calculate sum of digits
        int n = num, sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }

        write(pipeBA[1], &sum, sizeof(sum)); // Send result to A
        close(pipeBA[1]);

        return 0;
    }

    // Create process C
    int C = fork();

    if (C == 0) {
        // CHILD PROCESS C

        close(pipeAC[1]); // Close write end (C reads only)
        close(pipeCA[0]); // Close read end (C writes only)

        int num;
        read(pipeAC[0], &num, sizeof(num)); // Read number from A
        close(pipeAC[0]);

        printf("Process C (PID - %d, PPID - %d)\n", getpid(), getppid());

        // Check if even or odd
        int check = (num % 2 == 0) ? 1 : 0;

        write(pipeCA[1], &check, sizeof(check)); // Send result to A
        close(pipeCA[1]);

        return 0;
    }

    // PARENT PROCESS A
    printf("Process A (PID - %d, PPID - %d), index - %d\n",
           getpid(), getppid(), index);

    // Send data to B
    close(pipeAB[0]); // Close read end
    write(pipeAB[1], &index, sizeof(index)); // FIXED (was WRITE)
    close(pipeAB[1]);

    // Send data to C
    close(pipeAC[0]); // Close read end
    write(pipeAC[1], &index, sizeof(index));
    close(pipeAC[1]);

    // Receive result from B
    close(pipeBA[1]); // Close write end
    int sum;
    read(pipeBA[0], &sum, sizeof(sum)); // FIXED (missing semicolon)
    close(pipeBA[0]);

    // Receive result from C
    close(pipeCA[1]); // Close write end
    int check;
    read(pipeCA[0], &check, sizeof(check));
    close(pipeCA[0]);

    // Display results
    printf("Digit sum received from B = %d\n", sum);

    if (check == 1) {
        printf("C says: %d is Even\n", index);
    } else {
        printf("C says: %d is Odd\n", index);
    }

    return 0;
}