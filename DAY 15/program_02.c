#include <stdio.h>
#include <unistd.h>

int main() {
    int c_to_p[3][2];
    float val[3], res;
    char unit[3];

    for (int i = 0; i < 3; i++) {
        pipe(c_to_p[i]);
    }

    printf("Enter three temperatures (Eg: 25C 77F 300K):\n");

    for (int i = 0; i < 3; i++) {

        scanf("%f%c", &val[i], &unit[i]);

        if (fork() == 0) {

            close(c_to_p[i][0]); // close read end

            float result = 0;

            if (i == 0 && (unit[i] == 'C' || unit[i] == 'c')) {
                result = (val[i] * 9 / 5) + 32;
            }
            else if (i == 1 && (unit[i] == 'F' || unit[i] == 'f')) {
                result = (val[i] - 32) * 5 / 9;
            }
            else if (i == 2 && (unit[i] == 'K' || unit[i] == 'k')) {
                result = val[i] - 273.15;
            }

            write(c_to_p[i][1], &result, sizeof(result));

            close(c_to_p[i][1]);

            return 0;
        }

        close(c_to_p[i][1]); // parent closes write end
    }

    // Parent reads results
    for (int i = 0; i < 3; i++) {

        read(c_to_p[i][0], &res, sizeof(res));

        if (i == 0)
            printf("Child 1 (C to F): %.2f F\n", res);

        else if (i == 1)
            printf("Child 2 (F to C): %.2f C\n", res);

        else if (i == 2)
            printf("Child 3 (K to C): %.2f C\n", res);

        close(c_to_p[i][0]);
    }

    return 0;
}