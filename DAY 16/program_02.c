#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

int main() {
    int index = 372;
    int parentChild[2][2];

    for(int i = 0; i < 2; i++) {
        if(pipe(parentChild[i]) == -1) {
            perror("Pipe Failed!");
            exit(1);
        }
    }

    pid_t B = fork();
    if(B == 0) {
        close(parentChild[0][1]);

        int num;
        read(parentChild[0][0], &num, sizeof(num));
        close(parentChild[0][0]);

        printf("Process B (PID: %d, PPID: %d)\n", getpid(), getppid());

        int sum = 0, n = num;
        while(n > 0) {
            sum += n % 10;
            n /= 10;
        }

        printf("Digit sum of %d = %d", num, sum);
        return 0;
    }

    pid_t C = fork();
    if(C == 0) {
        close(parentChild[1][1]);

        int num;
        read(parentChild[1][0], &num, sizeof(num));
        close(parentChild[1][0]);

        printf("Process C (PID: %d, PPID: %d)\n", getpid(), getppid());
        
        if(num % 2 == 0) {
            printf("%d is even!\n", num);
        } else {
            printf("%d is odd!\n", num);
        }
        return 0;
    }

    printf("Process A (PID: %d, PPID: %d), index: %d\n", getpid(), getppid(), index);

    for(int i = 0; i < 2; i++) {
        close(parentChild[i][0]);
        write(parentChild[i][1], &index, sizeof(index));
        close(parentChild[i][1]);
    }

    return 0;
}