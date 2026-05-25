#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

void show(char name[], int level) {
    printf("%s | PID=%d | PPID=%d | Level=%d\n", name, getpid(), getppid(), level);
}

/* ---------- Level 2 Tasks ---------- */

void fileBackupChildren() {
    if (fork() == 0) {
        show("Read Files", 2);
        exit(0);
    }

    if (fork() == 0) {
        show("Write Backup", 2);
        exit(0);
    }
}

void networkMonitoringChildren() {
    if (fork() == 0) {
        show("Capture Packets", 2);
        exit(0);
    }

    if (fork() == 0) {
        show("Analyse Traffic", 2);
        exit(0);
    }
}

/* ---------- Level 1 Tasks ---------- */

void fileBackup() {
    show("File Backup", 1);
    fileBackupChildren();
}

void networkMonitoring() {
    show("Network Monitoring", 1);
    networkMonitoringChildren();
}

void logCleanup() {
    show("Log Cleanup", 1);
}

/* ---------- Main ---------- */

int main() {
    show("Main Task Manager", 0);

    for (int i = 1; i <= 3; i++) {
        if (fork() == 0) {
            switch (i) {
                case 1: {
                    fileBackup();
                    break;
                }

                case 2: {
                    networkMonitoring();
                    break;
                }

                case 3: {
                    logCleanup();
                    break;
                }
            }

            exit(0);
        }
    }

    return 0;
}