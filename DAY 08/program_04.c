#include <stdio.h>
#include <unistd.h>
#include <sys/msg.h>
#include <string.h>
#include <stdlib.h>

#define MAXSIZE 128
#define MSGKEY 1111

struct person {
    long mtype;
    int age;
    char name[100];
    char regno[100];
};

int main() {
    int msgid;
    struct person p1, p2;
    int f = fork();

    if (f == 0) {
        msgid = msgget(MSGKEY, IPC_CREAT | 0666);

        msgrcv(msgid, &p2, sizeof(p2) - sizeof(long), 1, 0);

        printf("Received name: %s\n", p2.name);
        printf("Received reg.no: %s\n", p2.regno);
        printf("Received age: %d\n", p2.age);

        msgctl(msgid, IPC_RMID, NULL);
    } else {
        msgid = msgget(MSGKEY, IPC_CREAT | 0666);

        printf("Enter a name: ");
        scanf("%s", p1.name);

        printf("Enter a reg.no: ");
        scanf("%s", p1.regno);

        printf("Enter an age: ");
        scanf("%d", &p1.age);

        p1.mtype = 1;

        int buflen = sizeof(p1) - sizeof(long);

        if (msgsnd(msgid, &p1, buflen, 0) < 0) {
            perror("Message not sent");
        } else {
            printf("Message sent!\n");
        }
    }

    return 0;
}