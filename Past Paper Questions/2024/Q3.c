#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>

char upper(char c)
{
    if(c >= 'a' && c <= 'z')
        return c - 32;
    return c;
}

int main()
{
    int p1[2], p2[2], p3[2];
    int r1[2], r2[2], r3[2];

    float t1, t2, t3;
    float a1, a2, a3;

    char s1, s2, s3, ch;

    pipe(p1); pipe(p2); pipe(p3);
    pipe(r1); pipe(r2); pipe(r3);

    printf("Enter first temperature: ");
    scanf("%f %c", &t1, &s1);

    printf("Enter second temperature: ");
    scanf("%f %c", &t2, &s2);

    printf("Enter third temperature: ");
    scanf("%f %c", &t3, &s3);

    s1 = upper(s1);
    s2 = upper(s2);
    s3 = upper(s3);

    if(fork() == 0)
    {
        float t;

        read(p1[0], &t, sizeof(t));
        read(p1[0], &ch, sizeof(ch));

        printf("Child1 PID=%d PPID=%d\n", getpid(), getppid());

        a1 = t * 9 / 5 + 32;

        write(r1[1], &a1, sizeof(a1));
        exit(0);
    }

    if(fork() == 0)
    {
        float t;

        read(p2[0], &t, sizeof(t));
        read(p2[0], &ch, sizeof(ch));

        printf("Child2 PID=%d PPID=%d\n", getpid(), getppid());

        a2 = (t - 32) * 5 / 9;

        write(r2[1], &a2, sizeof(a2));
        exit(0);
    }

    if(fork() == 0)
    {
        float t;

        read(p3[0], &t, sizeof(t));
        read(p3[0], &ch, sizeof(ch));

        printf("Child3 PID=%d PPID=%d\n", getpid(), getppid());

        a3 = t - 273.15;

        write(r3[1], &a3, sizeof(a3));
        exit(0);
    }

    write(p1[1], &t1, sizeof(t1));
    write(p1[1], &s1, sizeof(s1));

    write(p2[1], &t2, sizeof(t2));
    write(p2[1], &s2, sizeof(s2));

    write(p3[1], &t3, sizeof(t3));
    write(p3[1], &s3, sizeof(s3));

    read(r1[0], &a1, sizeof(a1));
    read(r2[0], &a2, sizeof(a2));
    read(r3[0], &a3, sizeof(a3));

    printf("\nParent PID=%d\n", getpid());

    printf("%.2f%c = %.2f F\n", t1, s1, a1);
    printf("%.2f%c = %.2f C\n", t2, s2, a2);
    printf("%.2f%c = %.2f C\n", t3, s3, a3);

    return 0;
}