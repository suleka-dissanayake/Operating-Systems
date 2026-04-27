#include <stdio.h>
#include <unistd.h>
#include <string.h>

int main() {
    int p_to_c[3][2], c_to_p[3][2];
    float val;
    char unit;

    for (int i = 0; i < 3; i++) {
        pipe(p_to_c[i]);
        pipe(c_to_p[i]);
    }

    printf("Enter three temperatures (Eg: 25C 77F 300K):\n");

    for (int i = 0; i < 3; i++) {
        scanf("%f%c", &val, &unit);

        if (fork() == 0) {
            float result;
            if (i == 0 && (unit == 'C' || unit == 'c')) {
                result = (val * 9 / 5) + 32;
                write(c_to_p[0][1], &result, sizeof(result));
            } 
            else if (i == 1 && (unit == 'F' || unit == 'f')) {
                result = (val - 32) * 5 / 9;
                write(c_to_p[1][1], &result, sizeof(result));
            } 
            else if (i == 2 && (unit == 'K' || unit == 'k')) {
                result = val - 273.15;
                write(c_to_p[2][1], &result, sizeof(result));
            }
            return 0;
        }
    }

    float res;
    sleep(1);
    
    if (read(c_to_p[0][1] ? c_to_p[0][0] : -1, &res, sizeof(res)) > 0)
        printf("Child 1 (C to F): %.2f F\n", res);
    if (read(c_to_p[1][0], &res, sizeof(res)) > 0)
        printf("Child 2 (F to C): %.2f C\n", res);
    if (read(c_to_p[2][0], &res, sizeof(res)) > 0)
        printf("Child 3 (K to C): %.2f C\n", res);

    return 0;
}