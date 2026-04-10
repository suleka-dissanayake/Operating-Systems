#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int index = 372;  // Number to process

    // Pipes:
    // AB: A → B
    // BA: B → A
    // BC: B → C
    // CA: C → A
    int pipeAB[2], pipeBA[2];
    int pipeBC[2], pipeCA[2];

    // Create pipes
    pipe(pipeAB);
    pipe(pipeBA);
    pipe(pipeBC);
    pipe(pipeCA);

    // Create process B
    int B = fork();

    if (B == 0) {
        // CHILD PROCESS B

        close(pipeAB[1]); // Close write end (B only reads from A)
        close(pipeBA[0]); // Close read end (B only writes to A)
        close(pipeBC[0]); // Close read end (B only writes to C)
        close(pipeCA[1]); // Close write end (B only reads from C)

        int num;
        read(pipeAB[0], &num, sizeof(num)); // Read number from A
        close(pipeAB[0]);

        printf("Process B (PID - %d, PPID - %d)\n", getpid(), getppid());

        // Check if even or odd
        int check = (num % 2 == 0) ? 1 : 0;

        write(pipeBC[1], &check, sizeof(check)); // Send result to C
        close(pipeBC[1]);

        // Send the sum of digits to A (A will read it later)
        int n = num, sum = 0;
        while (n > 0) {
            sum += n % 10;
            n /= 10;
        }

        write(pipeBA[1], &sum, sizeof(sum)); // Send sum to A
        close(pipeBA[1]);

        return 0;
    }

    // Create process C
    int C = fork();

    if (C == 0) {
        // CHILD PROCESS C

        close(pipeBC[1]); // Close write end (C only reads from B)
        close(pipeCA[0]); // Close read end (C only writes to A)

        int check;
        read(pipeBC[0], &check, sizeof(check)); // Read even/odd check from B
        close(pipeBC[0]);

        printf("Process C (PID - %d, PPID - %d)\n", getpid(), getppid());

        // Reverse the number
        int num = 372; // Hardcoded, or could be passed from another process
        int reversed = 0;
        while (num != 0) {
            reversed = reversed * 10 + num % 10;
            num /= 10;
        }

        write(pipeCA[1], &reversed, sizeof(reversed)); // Send reversed number to A
        close(pipeCA[1]);

        return 0;
    }

    // PARENT PROCESS A
    printf("Process A (PID - %d, PPID - %d), index - %d\n", getpid(), getppid(), index);

    // Send data to B
    close(pipeAB[0]); // Close read end
    write(pipeAB[1], &index, sizeof(index)); // Send number to B
    close(pipeAB[1]);

    // Receive sum of digits from B
    close(pipeBA[1]); // Close write end
    int sum;
    read(pipeBA[0], &sum, sizeof(sum)); // Get sum of digits from B
    close(pipeBA[0]);

    // Receive even/odd result from C
    close(pipeBC[1]); // Close write end
    int check;
    read(pipeBC[0], &check, sizeof(check)); // Get even/odd result from C
    close(pipeBC[0]);

    // Receive reversed number from C
    close(pipeCA[1]); // Close write end
    int reversed;
    read(pipeCA[0], &reversed, sizeof(reversed)); // Get reversed number from C
    close(pipeCA[0]);

    // Display results
    printf("Sum of digits received from B = %d\n", sum);

    if (check == 1) {
        printf("C says: %d is Even\n", index);
    } else {
        printf("C says: %d is Odd\n", index);
    }

    printf("Reversed number received from C = %d\n", reversed);

    return 0;
}