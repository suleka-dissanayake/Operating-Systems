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
        char grade[100];
    } p2 = {0};

    int msgqid = msgget(MSGKEY, IPC_CREAT | 0666);
    if (msgqid == -1) {
        perror("msgget");
        return 1;
    }

    if (msgrcv(msgqid, &p2, sizeof(p2) - sizeof(p2.mtype), 0, 0) == -1) {
        perror("msgrcv");
        return 1;
    }

    printf("Name: %s\n", p2.name);
    printf("RegNo: %s\n", p2.regno);
    printf("Age: %d\n", p2.age);
    printf("Grade: %s\n", p2.grade);

    return 0;
}