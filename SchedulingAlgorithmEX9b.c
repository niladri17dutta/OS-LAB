#include <stdio.h>

int main() {
    int n, tq, total_time = 0, completed = 0;
    printf("Enter number of processes and time quantum: ");
    scanf("%d %d", &n, &tq);
    
    int bt[n], rt[n], wt = 0, tat = 0;  // Burst Time, Remaining Time, Waiting Time, Turnaround Time

    for (int i = 0; i < n; i++) {
        printf("Enter burst time for process %d: ", i + 1);
        scanf("%d", &bt[i]);
        rt[i] = bt[i];  // Initialize remaining time
    }

    while (completed < n) {
        for (int i = 0; i < n; i++) {
            if (rt[i] > 0) {
                int exec_time = (rt[i] > tq) ? tq : rt[i];
                total_time += exec_time;
                rt[i] -= exec_time;
                if (rt[i] == 0) {
                    wt += total_time - bt[i];    // Waiting Time
                    tat += total_time;           // Turnaround Time
                    completed++;
                }
            }
        }
    }

    printf("Average Waiting Time: %.2f\n", (float)wt / n);
    printf("Average Turnaround Time: %.2f\n", (float)tat / n);
    return 0;
}
