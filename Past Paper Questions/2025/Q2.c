#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

void show(char name[], int level)
{
    printf("%s PID=%d PPID=%d Level=%d\n",
           name, getpid(), getppid(), level);
}

int main()
{
    int i;

    show("Main Task Manager",0);

    for(i=1;i<=3;i++)
    {
        if(fork()==0)
        {
            if(i==1)
            {
                show("File Backup",1);

                if(fork()==0)
                {
                    show("Read Files",2);
                    exit(0);
                }

                if(fork()==0)
                {
                    show("Write Backup",2);
                    exit(0);
                }
            }

            if(i==2)
            {
                show("Network Monitoring",1);

                if(fork()==0)
                {
                    show("Capture Packets",2);
                    exit(0);
                }

                if(fork()==0)
                {
                    show("Analyse Traffic",2);
                    exit(0);
                }
            }

            if(i==3)
            {
                show("Log Cleanup",1);
            }

            exit(0);
        }
    }

    return 0;
}