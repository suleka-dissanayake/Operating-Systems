#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
    int p[2];
    int n,i,heart,oxygen;
    int critical=0;

    char name[50];

    pipe(p);

    printf("Enter number of patients: ");
    scanf("%d",&n);

    if(fork()==0)
    {
        close(p[1]);

        printf("\nPatient Report\n");

        for(i=0;i<n;i++)
        {
            read(p[0],name,sizeof(name));
            read(p[0],&heart,sizeof(int));
            read(p[0],&oxygen,sizeof(int));

            printf("%s ",name);
            printf("%d ",heart);
            printf("%d%% ",oxygen);

            if(heart<60 || heart>100 || oxygen<90)
            {
                printf("CRITICAL\n");
                critical++;
            }
            else if((heart>=60 && heart<=65) ||
                    (heart>=95 && heart<=100) ||
                    (oxygen>=90 && oxygen<=92))
            {
                printf("ALERT\n");
            }
            else
            {
                printf("STABLE\n");
            }
        }

        printf("Critical Cases = %d\n",critical);
    }
    else
    {
        close(p[0]);

        for(i=0;i<n;i++)
        {
            printf("\nName: ");
            scanf("%s",name);

            printf("Heart Rate: ");
            scanf("%d",&heart);

            printf("Oxygen Level: ");
            scanf("%d",&oxygen);

            write(p[1],name,sizeof(name));
            write(p[1],&heart,sizeof(int));
            write(p[1],&oxygen,sizeof(int));
        }
    }

    return 0;
}