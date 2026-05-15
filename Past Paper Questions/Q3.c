#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {
    // අපගේ පයිප්ප (pipes) 3 සඳහා array descriptors (0 - කියවීමට, 1 - ලිවීමට)
    int pipeA[2], pipeB[2], pipeC[2];
    int child_pid, grandchild_pid; // Process ID ගබඩා කිරීමට

    // පයිප්ප 3 නිර්මාණය කිරීම (pipeA, pipeB, pipeC)
    // දෝෂයක් සිදුවුවහොත් වැඩසටහන නවතා දමයි
    if (pipe(pipeA) == -1 || pipe(pipeB) == -1 || pipe(pipeC) == -1) {
        perror("Error: Pipe creation failed");
        exit(1);
    }

    // පළමු child process එක සෑදීමට fork() භාවිතා කිරීම
    child_pid = fork();

    if (child_pid < 0) {
        perror("Error: Fork failed");
        exit(1);
    }

    if (child_pid > 0) {
        // ==========================================
        // මව් ක්‍රියාවලිය (PARENT PROCESS)
        // ==========================================
        
        // භාවිතා නොකරන පයිප්ප කෙළවරවල් (pipe ends) වසා දැමීම
        close(pipeA[0]); // Parent ලියනවා පමණි, කියවන්නේ නැත (Pipe A)
        close(pipeB[0]); close(pipeB[1]); // Parent Pipe B භාවිතා කරන්නේ නැත
        close(pipeC[1]); // Parent කියවනවා පමණි, ලියන්නේ නැත (Pipe C)

        int n;
        printf("Enter the number of integers (N): ");
        scanf("%d", &n);

        int *arr = (int *)malloc(n * sizeof(int));
        printf("Enter %d integers:\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        printf("[Parent] PID: %d, PPID: %d, Activity: Sending N and array to Child\n", getpid(), getppid());

        // Pipe A හරහා N අගය සහ සංඛ්‍යා ලැයිස්තුව child process වෙත යැවීම
        write(pipeA[1], &n, sizeof(int));
        write(pipeA[1], arr, n * sizeof(int));
        
        close(pipeA[1]); // යැවීම අවසන් වූ පසු ලිවීමේ කෙළවර වසා දැමීම
        free(arr);

        // Pipe C හරහා grandchild process එකෙන් අවසන් සාමාන්‍යය (average) කියවීම
        // මෙහිදී read() ශ්‍රිතය, grandchild විසින් දත්ත එවන තුරු parent process එක තාවකාලිකව නවතාගෙන සිටී (Blocking)
        float average;
        read(pipeC[0], &average, sizeof(float));
        printf("[Parent] PID: %d, PPID: %d, Activity: Received average, Value: %.2f\n", getpid(), getppid(), average);
        
        close(pipeC[0]);

    } else {
        // ==========================================
        // ළමා ක්‍රියාවලිය (CHILD PROCESS)
        // ==========================================
        
        // Grandchild process එක සෑදීම
        grandchild_pid = fork();

        if (grandchild_pid < 0) {
            perror("Error: Fork failed");
            exit(1);
        }

        if (grandchild_pid > 0) {
            // තවමත් CHILD PROCESS එක තුළ
            
            // භාවිතා නොකරන පයිප්ප කෙළවරවල් වසා දැමීම
            close(pipeA[1]); // Child කියවනවා පමණි (Pipe A)
            close(pipeB[0]); // Child ලියනවා පමණි (Pipe B)
            close(pipeC[0]); close(pipeC[1]); // Child Pipe C භාවිතා කරන්නේ නැත

            int n;
            // Pipe A හරහා Parent එවන N අගය කියවීම (Parent ලියන තුරු මෙය block වී පවතී)
            read(pipeA[0], &n, sizeof(int));

            int *arr = (int *)malloc(n * sizeof(int));
            // Pipe A හරහා සංඛ්‍යා ලැයිස්තුව කියවීම
            read(pipeA[0], arr, n * sizeof(int));
            close(pipeA[0]);

            // සංඛ්‍යාවල එකතුව (sum) ගණනය කිරීම
            int sum = 0;
            for (int i = 0; i < n; i++) {
                sum += arr[i];
            }

            printf("[Child] PID: %d, PPID: %d, Activity: Calculated sum, Value: %d\n", getpid(), getppid(), sum);

            // Pipe B හරහා N අගය සහ එකතුව (sum) grandchild වෙත යැවීම
            write(pipeB[1], &n, sizeof(int));
            write(pipeB[1], &sum, sizeof(int));
            
            close(pipeB[1]);
            free(arr);

        } else {
            // ==========================================
            // මුණුබුරු ක්‍රියාවලිය (GRANDCHILD PROCESS)
            // ==========================================
            
            // භාවිතා නොකරන පයිප්ප කෙළවරවල් වසා දැමීම
            close(pipeA[0]); close(pipeA[1]); // Grandchild Pipe A භාවිතා කරන්නේ නැත
            close(pipeB[1]); // Grandchild කියවනවා පමණි (Pipe B)
            close(pipeC[0]); // Grandchild ලියනවා පමණි (Pipe C)

            int n, sum;
            // Pipe B හරහා Child එවන N අගය සහ එකතුව කියවීම (Child ලියන තුරු block වී පවතී)
            read(pipeB[0], &n, sizeof(int));
            read(pipeB[0], &sum, sizeof(int));
            close(pipeB[0]);

            // සාමාන්‍යය (average) ගණනය කිරීම
            float average = (float)sum / n;

            printf("[Grandchild] PID: %d, PPID: %d, Activity: Calculated average, Value: %.2f\n", getpid(), getppid(), average);

            // Pipe C හරහා සාමාන්‍යය නැවත Parent වෙත යැවීම
            write(pipeC[1], &average, sizeof(float));
            close(pipeC[1]);
        }
    }

    return 0;
}