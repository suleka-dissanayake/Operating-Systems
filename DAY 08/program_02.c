#include <stdio.h>
#include <unistd.h>

int main() {
    pid_t childPID = fork();

    if (childPID == -1) {
        printf("Failed to fork!");
        return -1;
    } else if (childPID == 0){
        for(int i = 0; i < 5; i++) {
            printf("Child\n");
        }
    } else {
        for(int i = 0; i < 5; i++) {
            printf("Parent\n");
        }
    }

    return 0;
}