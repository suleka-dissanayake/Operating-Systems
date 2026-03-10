#include <stdio.h>
#include <unistd.h>

int main() {
    fork();
    fork();
    printf("I am %d and my PID is %d and PPID is %d\n", getpid(), getpid(), getpid());
    return 0;
}