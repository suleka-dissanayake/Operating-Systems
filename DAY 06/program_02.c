#include <stdio.h>
#include <unistd.h>

int main() {
    printf("A (PID: %d)\n", getpid());
    if (fork() == 0) {
        printf("B (PID: %d, Parent PID: %d)\n", getpid(), getppid());
        if (fork() == 0) {
            printf("C (PID: %d, Parent PID: %d)\n", getpid(), getppid());
        }
    }
    return 0;
}