#include <stdio.h>

void sortProcesses(int n, int burstTime[], int processID[]) {
    for (int i = 0; i < n-1; i++) {
        for (int j = i+1; j < n; j++) {
            if (burstTime[i] > burstTime[j]) {
                // Swap burst time
                int temp = burstTime[i];
                burstTime[i] = burstTime[j];
                burstTime[j] = temp;

                // Swap process ID
                temp = processID[i];
                processID[i] = processID[j];
                processID[j] = temp;
            }
        }
    }
}

void calculateTimes(int n, int burstTime[], int waitingTime[], int turnaroundTime[]) {
    waitingTime[0] = 0;  // First process has 0 waiting time
    turnaroundTime[0] = burstTime[0]; // Turnaround time of first process is its burst time

    for (int i = 1; i < n; i++) {
        waitingTime[i] = waitingTime[i-1] + burstTime[i-1];
        turnaroundTime[i] = waitingTime[i] + burstTime[i];
    }
}

void calculateAverageTimes(int n, int waitingTime[], int turnaroundTime[]) {
    float totalWaitingTime = 0, totalTurnaroundTime = 0;

    for (int i = 0; i < n; i++) {
        totalWaitingTime += waitingTime[i];
        totalTurnaroundTime += turnaroundTime[i];
    }

    printf("Average Waiting Time: %.2f\n", totalWaitingTime / n);
    printf("Average Turnaround Time: %.2f\n", totalTurnaroundTime / n);
}

void printProcessInfo(int n, int processID[], int burstTime[], int waitingTime[], int turnaroundTime[]) {
    printf("\nProcess\tBurst Time\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\n", processID[i], burstTime[i], waitingTime[i], turnaroundTime[i]);
    }
}

int main() {
    int n;

    printf("Enter the number of processes: ");
    scanf("%d", &n);

    int burstTime[n], processID[n], waitingTime[n], turnaroundTime[n];

    for (int i = 0; i < n; i++) {
        processID[i] = i+1; // Assigning process IDs starting from 1
        printf("Enter burst time for process %d: ", i+1);
        scanf("%d", &burstTime[i]);
    }

    // Step 4: Sort processes by burst time (ascending order)
    sortProcesses(n, burstTime, processID);

    // Step 5-7: Calculate waiting and turnaround times
    calculateTimes(n, burstTime, waitingTime, turnaroundTime);

    // Print the process info
    printProcessInfo(n, processID, burstTime, waitingTime, turnaroundTime);

    // Step 8: Calculate and print average waiting and turnaround times
    calculateAverageTimes(n, waitingTime, turnaroundTime);

    return 0;
}
