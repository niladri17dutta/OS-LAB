#include <stdio.h>

int n, m, Allocation[10][10], Max[10][10], Need[10][10], Available[10], Finish[10];

// Calculate Need matrix as Need = Max - Allocation
void calculateNeed() {
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            Need[i][j] = Max[i][j] - Allocation[i][j];
}

// Check if the system is in a safe state
int isSafe() {
    int Work[10], count = 0;
    for (int i = 0; i < m; i++) Work[i] = Available[i];
    for (int i = 0; i < n; i++) Finish[i] = 0;

    while (count < n) {
        int found = 0;
        for (int i = 0; i < n; i++) {
            if (!Finish[i]) {
                int flag = 1;
                for (int j = 0; j < m; j++)
                    if (Need[i][j] > Work[j]) { flag = 0; break; }

                if (flag) {
                    for (int j = 0; j < m; j++) Work[j] += Allocation[i][j];
                    Finish[i] = 1;
                    count++;
                    found = 1;
                }
            }
        }
        if (!found) return 0;  // Not safe if no process can finish
    }
    return 1;
}

// Handle resource requests
void requestResources(int processId, int Request[]) {
    for (int i = 0; i < m; i++)
        if (Request[i] > Need[processId][i] || Request[i] > Available[i]) {
            printf("Request cannot be granted.\n");
            return;
        }

    // Temporarily allocate resources
    for (int i = 0; i < m; i++) {
        Available[i] -= Request[i];
        Allocation[processId][i] += Request[i];
        Need[processId][i] -= Request[i];
    }

    if (isSafe()) printf("Request granted.\n");
    else {
        // Rollback if not safe
        for (int i = 0; i < m; i++) {
            Available[i] += Request[i];
            Allocation[processId][i] -= Request[i];
            Need[processId][i] += Request[i];
        }
        printf("Request cannot be granted. System not safe.\n");
    }
}

int main() {
    printf("Enter number of processes and resources: ");
    scanf("%d %d", &n, &m);

    printf("Enter Allocation matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &Allocation[i][j]);

    printf("Enter Max matrix:\n");
    for (int i = 0; i < n; i++)
        for (int j = 0; j < m; j++)
            scanf("%d", &Max[i][j]);

    printf("Enter Available resources: ");
    for (int i = 0; i < m; i++)
        scanf("%d", &Available[i]);

    calculateNeed();
    
    int processId, Request[10];
    printf("Enter process ID and request vector: ");
    scanf("%d", &processId);
    for (int i = 0; i < m; i++)
        scanf("%d", &Request[i]);

    requestResources(processId, Request);
    
    return 0;
}
