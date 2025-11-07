#include <stdio.h>

int main() {
    int n, m; // n = number of processes, m = number of resources

    int alloc[10][10], max[10][10], avail[10];
    int need[10][10], finish[10], safeSeq[10];

    // Input: number of processes and resources
    printf("Enter number of processes: ");
    scanf("%d", &n);

    printf("Enter number of resources: ");
    scanf("%d", &m);

    // Input Allocation Matrix
    printf("Enter Allocation Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &alloc[i][j]);
        }
    }

    // Input Max Matrix
    printf("Enter Maximum Matrix (%d x %d):\n", n, m);
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            scanf("%d", &max[i][j]);
        }
    }

    // Input Available Resources
    printf("Enter Available Resources (%d values):\n", m);
    for (int j = 0; j < m; j++) {
        scanf("%d", &avail[j]);
    }

    // Calculate Need Matrix: Need = Max - Allocation
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            need[i][j] = max[i][j] - alloc[i][j];
        }
    }

    // Initialize finish[] for all processes as 0 (not finished)
    for (int i = 0; i < n; i++) {
        finish[i] = 0;
    }

    int count = 0; // Count of finished processes

    // SAFETY ALGORITHM STARTS
    while (count < n) {
        int found = 0; // flag to check if a process can execute in this round

        // Loop through all processes
        for (int i = 0; i < n; i++) {
            if (finish[i] == 0) { // If not yet finished
                int canRun = 1;  // Assume it can run

                // Check if need <= available for all resources
                for (int j = 0; j < m; j++) {
                    if (need[i][j] > avail[j]) {
                        canRun = 0; // Not enough resources
                        break;
                    }
                }

                // If process can run safely
                if (canRun == 1) {
                    // Pretend the process runs and releases resources
                    for (int j = 0; j < m; j++) {
                        avail[j] += alloc[i][j];
                    }

                    // Mark as finished
                    finish[i] = 1;

                    // Add to safe sequence
                    safeSeq[count++] = i;

                    found = 1;
                }
            }
        }

        // If no process could run in this pass → unsafe
        if (found == 0) {
            printf("\nSystem is NOT in a safe state!\n");
            return 0;
        }
    }

    // If all processes finished safely
    printf("\nSystem is in a SAFE STATE.\nSafe Sequence: ");
    for (int i = 0; i < n; i++)
        printf("P%d ", safeSeq[i]);
    printf("\n");

    return 0;
}
