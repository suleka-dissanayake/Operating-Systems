#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int index = 372;

    int pipeAB[2], pipeBA[2];
    int pipeBC[2], pipeCA[2];

    pipe(pipeAB);
    pipe(pipeBA);
    pipe(pipeBC);
    pipe(pipeCA);

    pid_t B, C;

    // Create Process B
    B = fork();

    if (B == 0) {
        // PROCESS B
        close(pipeAB[1]);
        close(pipeBA[0]);
        close(pipeBC[0]);
        close(pipeCA[1]);

        int num;
        read(pipeAB[0], &num, sizeof(num));
        close(pipeAB[0]);

        printf("Process B (PID=%d, PPID=%d)\n", getpid(), getppid());

        int check;
        if (num % 2 == 0)
            check = 1;
        else
            check = 0;

        write(pipeBC[1], &check, sizeof(check));
        close(pipeBC[1]);

        int sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }

        write(pipeBA[1], &sum, sizeof(sum));
        close(pipeBA[1]);

        exit(0);
    }
    else {
        // Parent creates Process C
        C = fork();

        if (C == 0) {
            // PROCESS C
            close(pipeBC[1]);
            close(pipeCA[0]);

            int check;
            read(pipeBC[0], &check, sizeof(check));
            close(pipeBC[0]);

            printf("Process C (PID=%d, PPID=%d)\n", getpid(), getppid());

            int num = 372;
            int reversed = 0;

            while (num > 0) {
                reversed = reversed * 10 + num % 10;
                num /= 10;
            }

            write(pipeCA[1], &reversed, sizeof(reversed));
            close(pipeCA[1]);

            exit(0);
        }
        else {
            // PROCESS A (PARENT)
            printf("Process A (PID=%d, PPID=%d), Index=%d\n", getpid(), getppid(), index);

            close(pipeAB[0]);
            write(pipeAB[1], &index, sizeof(index));
            close(pipeAB[1]);

            close(pipeBA[1]);
            int sum;
            read(pipeBA[0], &sum, sizeof(sum));
            close(pipeBA[0]);

            close(pipeBC[1]);
            int check;
            read(pipeBC[0], &check, sizeof(check));
            close(pipeBC[0]);

            close(pipeCA[1]);
            int reversed;
            read(pipeCA[0], &reversed, sizeof(reversed));
            close(pipeCA[0]);

            printf("Sum of digits from B = %d\n", sum);

            if (check == 1)
                printf("%d is Even\n", index);
            else
                printf("%d is Odd\n", index);

            printf("Reversed number from C = %d\n", reversed);
        }
    }

    return 0;
}