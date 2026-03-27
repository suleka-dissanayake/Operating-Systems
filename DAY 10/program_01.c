#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
#include <string.h>

int main() {
    int pipefd[2];

    if (pipe(pipefd) == -1) {
        perror("pipe");
        exit(EXIT_FAILURE);
    }

    pid_t childpid = fork();

    if (childpid == -1) {
        perror("fork");
        exit(EXIT_FAILURE);
    }

    if (childpid == 0) {
        close(pipefd[1]);

        char buffer[100];
        ssize_t bytesRead = read(pipefd[0], buffer, sizeof(buffer));

        if (bytesRead == -1) {
            perror("read");
            exit(EXIT_FAILURE);
        }

        printf("Child process: Received message from parent: %.*s\n",
               (int)bytesRead, buffer);

        close(pipefd[0]);
        exit(EXIT_SUCCESS);

    } else {
        close(pipefd[0]);

        const char* message = "Hello from parent!";
        ssize_t bytesWritten = write(pipefd[1], message, strlen(message));

        if (bytesWritten == -1) {
            perror("write");
            exit(EXIT_FAILURE);
        }

        close(pipefd[1]);
        wait(NULL); 
    }

    return 0;
}