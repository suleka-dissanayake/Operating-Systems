#include <stdio.h>
#include <string.h>
#include <sys/ipc.h>
#include <sys/msg.h>
#include <unistd.h>
#include <stdlib.h>

#define MSGKEY 1111

int main() {
    struct person {
        long mtype;
        int age;
        char name[100];
        char regno[100];
    };

    struct person p1;
    p1.mtype = 1;

    int msqid = msgget(MSGKEY, IPC_CREAT | 0666);

    printf("Enter a name: ");
    scanf("%s", p1.name);

    printf("Enter a reg.no: ");
    scanf("%s", p1.regno);

    printf("Enter an age: ");
    scanf("%d", &p1.age);

    int buflen = sizeof(p1) - sizeof(long);

    if (msgsnd(msqid, &p1, buflen, IPC_NOWAIT) < 0) {
        perror("Message not sent");
    } else {
        printf("Message sent!\n");
    }

    return 0;
}