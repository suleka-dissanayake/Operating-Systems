#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/wait.h>

int main() {
    int index = 372;
    int pipeAB[2];
    int pipeAC[2];

    pipe(pipeAB);
    pipe(pipeAC);

    int B = fork();

    if(B == 0) {
        close(pipeAB[1]);
        int num;
        read(pipeAB[0], &num, sizeof(num));
        close(pipeAB[0]);

        printf("Process B (PID - %d, PPID - %d)\n", getpid(), getppid());

        int sum = 0;
        while(num > 0) {
            sum += num % 10;
            num /= 10;
        }
        printf("Digit sum = %d\n", sum);
        return 0;
    }

    int C = fork();

    if(C == 0) {
        close(pipeAC[1]);
        int num;
        read(pipeAC[0], &num, sizeof(num));
        close(pipeAC[0]);

        printf("Process C (PID - %d, PPID - %d)\n", getpid(), getppid());

        if(num % 2 == 0) {
            printf("%d is even\n", num);
        } else {
            printf("%d is odd\n", num);
        }
        return 0;
    }

    printf("Process A (PID - %d, PPID - %d), index - %d\n", getpid(), getppid(), index);

    close(pipeAB[0]);
    write(pipeAB[1], &index, sizeof(index));
    close(pipeAB[1]);

    close(pipeAC[0]);
    write(pipeAC[1], &index, sizeof(index));
    close(pipeAC[1]);

    wait(NULL);
    wait(NULL);

    return 0;
}