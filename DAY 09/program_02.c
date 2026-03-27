#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAXSIZE 128
#define MSGKEY 1111

int main() {
    char mtext[1000];
    int msqid = msgget(MSGKEY, IPC_CREAT | 0666);

    msgrcv(msqid, &mtext, 1024, 0, 0);
    printf("Received string: %s\n", mtext);
    msgctl(msqid, IPC_RMID, 0);

    return 0;
}