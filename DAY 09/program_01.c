#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MSGKEY 1111

int main() {
    key_t key = 15;
    int msqid;

    msqid = msgget(key, IPC_CREAT | 0644);
    if (msqid < 0) {
        printf("msgget failed!\n");
    } else {
        printf("Message queue created successfully with ID %d\n", msqid);
    }

    return 0;
}