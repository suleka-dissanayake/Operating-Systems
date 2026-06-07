#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int index = 372;

    int pipeAB[2], pipeBA[2];
    int pipeAC[2], pipeCA[2];

    pipe(pipeAB);
    pipe(pipeBA);
    pipe(pipeAC);
    pipe(pipeCA);

    pid_t B = fork();

    if (B == 0) {
        /* Process B */

        close(pipeAB[1]);
        close(pipeBA[0]);

        int num;
        read(pipeAB[0], &num, sizeof(num));

        printf("Process B (PID=%d, PPID=%d)\n", getpid(), getppid());

        int sum = 0;
        while (num > 0) {
            sum += num % 10;
            num /= 10;
        }

        write(pipeBA[1], &sum, sizeof(sum));

        close(pipeAB[0]);
        close(pipeBA[1]);

        exit(0);
    }
    else {
        /* Only Process A creates Process C */

        pid_t C = fork();

        if (C == 0) {
            /* Process C */

            close(pipeAC[1]);
            close(pipeCA[0]);

            int num;
            read(pipeAC[0], &num, sizeof(num));

            printf("Process C (PID=%d, PPID=%d)\n", getpid(), getppid());

            int check = (num % 2 == 0) ? 1 : 0;

            write(pipeCA[1], &check, sizeof(check));

            close(pipeAC[0]);
            close(pipeCA[1]);

            exit(0);
        }
        else {
            /* Parent Process A */

            printf("Process A (PID=%d, PPID=%d), Index=%d\n", getpid(), getppid(), index);

            /* Send number to B */
            close(pipeAB[0]);
            write(pipeAB[1], &index, sizeof(index));
            close(pipeAB[1]);

            /* Send number to C */
            close(pipeAC[0]);
            write(pipeAC[1], &index, sizeof(index));
            close(pipeAC[1]);

            /* Receive from B */
            close(pipeBA[1]);
            int sum;
            read(pipeBA[0], &sum, sizeof(sum));
            close(pipeBA[0]);

            /* Receive from C */
            close(pipeCA[1]);
            int check;
            read(pipeCA[0], &check, sizeof(check));
            close(pipeCA[0]);

            printf("Digit sum received from B = %d\n", sum);

            if (check)
                printf("C says: %d is Even\n", index);
            else
                printf("C says: %d is Odd\n", index);
        }
    }

    return 0;
}