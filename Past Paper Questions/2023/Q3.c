#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main() {

    // Pipes 3ක් සඳහා File Descriptors අරා (Arrays) ප්‍රකාශයට පත් කිරීම
    // pipe[0] = කියවීමට (Read), pipe[1] = ලිවීමට (Write)
    int pipeA[2], pipeB[2], pipeC[2];
    int child_pid, grandchild_pid;

    // Pipes 3 සාර්ථකව නිර්මාණය වුණාදැයි පරීක්ෂා කිරීම (අසමත් වුවහොත් -1 ලැබෙයි)
    if (pipe(pipeA) == -1 || pipe(pipeB) == -1 || pipe(pipeC) == -1) {
        perror("Error: Pipe creation failed");
        exit(1);
    }

    // පළමු Fork එක මඟින් Child Process එකක් සාදයි
    child_pid = fork();

    if (child_pid < 0) {
        perror("Error: Fork failed");
        exit(1);
    }

    // ==========================================
    // CHILD PROCESS (ළමා ක්‍රියාවලිය)
    // ==========================================
    if (child_pid == 0) {

        // Child process එක ඇතුළේ තවත් Fork එකක් මඟින් Grandchild Process එකක් සාදයි
        grandchild_pid = fork();

        if (grandchild_pid < 0) {
            perror("Error: Fork failed");
            exit(1);
        }

        // ==========================================
        // GRANDCHILD PROCESS (මුනුපුරු ක්‍රියාවලිය)
        // ==========================================
        if (grandchild_pid == 0) {

            // Grandchild ට pipeA අවශ්‍ය නැත. එබැවින් එහි දෙපැත්තම වසා දමයි.
            close(pipeA[0]);
            close(pipeA[1]);

            // pipeB මඟින් දත්ත කියවන නිසා එහි ලිවීමේ පැත්ත (Write end) වසා දමයි.
            close(pipeB[1]);

            // pipeC මඟින් දත්ත ලියන (යවන) නිසා එහි කියවීමේ පැත්ත (Read end) වසා දමයි.
            close(pipeC[0]);

            int n, sum;

            // Child විසින් pipeB එකට එවූ සංඛ්‍යා ගණන (n) සහ එකතුව (sum) කියවා ගනී.
            read(pipeB[0], &n, sizeof(int));
            read(pipeB[0], &sum, sizeof(int));

            // කියවා අවසන් වූ පසු pipeB හි කියවීමේ පැත්ත වසා දමයි.
            close(pipeB[0]);

            // සාමාන්‍යය (Average) ගණනය කිරීම
            float average = (float)sum / n;

            printf("[Grandchild] PID: %d, PPID: %d, Activity: Calculated average, Value: %.2f\n",
                   getpid(), getppid(), average);

            // ගණනය කළ සාමාන්‍යය pipeC හරහා Parent වෙත ලිවීම (යැවීම)
            write(pipeC[1], &average, sizeof(float));

            // වැඩේ ඉවර නිසා pipeC හි ලිවීමේ පැත්ත වසා දමයි.
            close(pipeC[1]);
        }

        // ==========================================
        // CHILD PROCESS (ළමා ක්‍රියාවලිය)
        // ==========================================
        else {

            // Child විසින් pipeA වෙතින් දත්ත කියවන නිසා එහි ලිවීමේ පැත්ත වසා දමයි.
            close(pipeA[1]);

            // pipeB වෙත දත්ත ලියන (යවන) නිසා එහි කියවීමේ පැත්ත වසා දමයි.
            close(pipeB[0]);

            // Child හට pipeC අවශ්‍ය නැත. එබැවින් එහි දෙපැත්තම වසා දමයි.
            close(pipeC[0]);
            close(pipeC[1]);

            int n;

            // Parent විසින් pipeA වෙත එවූ සංඛ්‍යා ගණන (n) කියවා ගනී.
            read(pipeA[0], &n, sizeof(int));

            // ලැබුණු සංඛ්‍යා ගණන අනුව Memory වෙන් කරගනී (Dynamic Memory Allocation)
            int *arr = (int *)malloc(n * sizeof(int));

            // Parent එවූ මුළු Array එකම pipeA වෙතින් කියවා ගනී.
            read(pipeA[0], arr, n * sizeof(int));

            // කියවා අවසන් වූ පසු pipeA හි කියවීමේ පැත්ත වසා දමයි.
            close(pipeA[0]);

            int sum = 0;

            // Array එකේ ඇති සියලුම සංඛ්‍යාවල එකතුව සෙවීම
            for (int i = 0; i < n; i++) {
                sum += arr[i];
            }

            printf("[Child] PID: %d, PPID: %d, Activity: Calculated sum, Value: %d\n",
                   getpid(), getppid(), sum);

            // සංඛ්‍යා ගණන (n) සහ එකතුව (sum) pipeB හරහා Grandchild වෙත යැවීම
            write(pipeB[1], &n, sizeof(int));
            write(pipeB[1], &sum, sizeof(int));

            // වැඩේ ඉවර නිසා pipeB හි ලිවීමේ පැත්ත වසා දමයි.
            close(pipeB[1]);

            // වෙන් කළ Memory නිදහස් කිරීම
            free(arr);
        }
    }

    // ==========================================
    // PARENT PROCESS (මව් ක්‍රියාවලිය)
    // ==========================================
    else {

        // Parent විසින් pipeA වෙත දත්ත ලියන නිසා එහි කියවීමේ පැත්ත වසා දමයි.
        close(pipeA[0]);

        // Parent හට pipeB අවශ්‍ය නැත. එබැවින් එහි දෙපැත්තම වසා දමයි.
        close(pipeB[0]);
        close(pipeB[1]);

        // pipeC මඟින් Grandchild ගෙන් දත්ත කියවන නිසා එහි ලිවීමේ පැත්ත වසා දමයි.
        close(pipeC[1]);

        int n;

        // පරිශීලකයාගෙන් සංඛ්‍යා කීයක් ඇතුළත් කරනවාදැයි ඇසීම
        printf("Enter the number of integers (N): ");
        scanf("%d", &n);

        int *arr = (int *)malloc(n * sizeof(int));

        // සංඛ්‍යාවන් එකින් එක Input කරවා ගැනීම
        printf("Enter %d integers:\n", n);
        for (int i = 0; i < n; i++) {
            scanf("%d", &arr[i]);
        }

        printf("[Parent] PID: %d, PPID: %d, Activity: Sending N and array to Child\n",
               getpid(), getppid());

        // සංඛ්‍යා ගණන (n) සහ සංඛ්‍යා අඩංගු Array එක pipeA හරහා Child වෙත යැවීම
        write(pipeA[1], &n, sizeof(int));
        write(pipeA[1], arr, n * sizeof(int));

        // යවා අවසන් වූ පසු pipeA හි ලිවීමේ පැත්ත වසා දමයි.
        close(pipeA[1]);

        // වෙන් කළ Memory නිදහස් කිරීම
        free(arr);

        float average;

        // Grandchild විසින් pipeC වෙත එවූ සාමාන්‍ය අගය (Average) කියවා ගැනීම (මෙහිදී Child සහ Grandchild වැඩේ ඉවර කරනකම් Parent බලා සිටී - Blocking Read)
        read(pipeC[0], &average, sizeof(float));

        printf("[Parent] PID: %d, PPID: %d, Activity: Received average, Value: %.2f\n",
               getpid(), getppid(), average);

        // වැඩේ ඉවර නිසා pipeC හි කියවීමේ පැත්ත වසා දමයි.
        close(pipeC[0]);
    }

    return 0;
}