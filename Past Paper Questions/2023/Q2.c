#include <stdio.h>
#include <threads.h>

int a, b;

int addition(void *arg)
{
    printf("Addition = %d\n", a + b);
    return 0;
}

int subtraction(void *arg)
{
    printf("Subtraction = %d\n", a - b);
    return 0;
}

int multiplication(void *arg)
{
    printf("Multiplication = %d\n", a * b);
    return 0;
}

int division(void *arg)
{
    if (b != 0)
        printf("Division = %.2f\n", (float)a / b);
    else
        printf("Division not possible (divide by zero)\n");

    return 0;
}

int main()
{
    thrd_t t1, t2, t3, t4;

    printf("Enter two integers: ");
    scanf("%d %d", &a, &b);

    thrd_create(&t1, addition, NULL);
    thrd_create(&t2, subtraction, NULL);
    thrd_create(&t3, multiplication, NULL);
    thrd_create(&t4, division, NULL);

    thrd_join(t1, NULL);
    thrd_join(t2, NULL);
    thrd_join(t3, NULL);
    thrd_join(t4, NULL);

    return 0;
}