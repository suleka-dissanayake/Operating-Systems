#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>

#define MAXSIZE 128
#define MSGKEY 1111

int main() {
    struct person {
        long mtype;
        int age;
        char name[100];
        char regno[100];
    } p2;

    int msgqid = msgget(MSGKEY, IPC_CREAT | 0666);
    if (msgqid == -1) {
        perror("msgget");
        return 1;
    }

    if (msgrcv(msgqid, &p2, sizeof(p2) - sizeof(long), 0, 0) == -1) {
        perror("msgrcv");
        return 1;
    }

    printf("Received name: %s\n", p2.name);
    printf("Received regno: %s\n", p2.regno);
    printf("Received age: %d\n", p2.age);

    if (msgctl(msgqid, IPC_RMID, 0) == -1) {
        perror("msgctl");
    }

    return 0;
}