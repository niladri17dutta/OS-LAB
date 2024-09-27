#include <stdio.h>

void findWaitingTime(int processes[], int n, int bt[], int wt[]) {
    wt[0] = 0;
    // Calculate waiting time for all other processes
    for (int i = 1; i < n; i++) {
        wt[i] = bt[i - 1] + wt[i - 1];
    }
}

void findTurnAroundTime(int processes[], int n, int bt[], int wt[], int tat[]) {
    // Calculate turnaround time by adding burst time and waiting time
    for (int i = 0; i < n; i++) {
        tat[i] = bt[i] + wt[i];
    }
}

void findavgTime(int processes[], int n, int bt[]) {
    int wt[n], tat[n];
    int total_wt = 0, total_tat = 0;
    // Function calls to calculate waiting time and turnaround time
    findWaitingTime(processes, n, bt, wt);
    findTurnAroundTime(processes, n, bt, wt, tat);
    // Calculate total waiting time and turnaround time
    for (int i = 0; i < n; i++) {
        total_wt += wt[i];
        total_tat += tat[i];
    }
    printf("Process\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t%d\t\t%d\t\t%d\n", processes[i], bt[i], wt[i], tat[i]);
    }
    printf("\nAverage Waiting Time = %.2f", (float)total_wt / n);
    printf("\nAverage Turnaround Time = %.2f\n", (float)total_tat / n);
}

int main() {
    int n;
    printf("Enter number of processes: ");
    scanf("%d", &n);
    int processes[n], burst_time[n];
    // Input process numbers and burst times
    printf("Enter process numbers (1 to %d):\n", n);
    for (int i = 0; i < n; i++) {
        processes[i] = i + 1;
    }
    printf("Enter burst times:\n");
    for (int i = 0; i < n; i++) {
        printf("Process %d: ", processes[i]);
        scanf("%d", &burst_time[i]);
    }
    // Calculate and display average times
    findavgTime(processes, n, burst_time);
    return 0;
}
