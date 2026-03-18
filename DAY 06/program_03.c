#include <stdio.h>
#include <unistd.h>

int main() {
    printf("A (PID: %d)\n", getpid());
    if (fork() == 0) {
        printf("B (Child PID: %d, Parent PID: %d)\n", getpid(), getppid());
    }
    else {
        if (fork() == 0) {
            printf("C (Child PID: %d, Parent PID: %d)\n", getpid(), getppid());
        }
    }
    return 0;
}