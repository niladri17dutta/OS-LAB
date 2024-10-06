#include <stdio.h>

// Structure to represent a process
struct Process {
    int id;        // Process ID
    int burstTime; // Burst time of the process
    int priority;  // Priority of the process
    int waitingTime;    // Waiting time of the process
    int turnaroundTime; // Turnaround time of the process
};

// Function to sort processes by priority (lower priority number = higher priority)
void sortByPriority(struct Process proc[], int n) {
    struct Process temp;
    for (int i = 0; i < n - 1; i++) {
        for (int j = i + 1; j < n; j++) {
            if (proc[i].priority > proc[j].priority) {
                temp = proc[i];
                proc[i] = proc[j];
                proc[j] = temp;
            }
        }
    }
}

// Function to calculate waiting and turnaround times
void calculateTimes(struct Process proc[], int n) {
    int totalWaitingTime = 0, totalTurnaroundTime = 0;
    
    // First process always has 0 waiting time
    proc[0].waitingTime = 0;
    proc[0].turnaroundTime = proc[0].burstTime;
    
    // Calculate waiting time and turnaround time for other processes
    for (int i = 1; i < n; i++) {
        proc[i].waitingTime = proc[i - 1].waitingTime + proc[i - 1].burstTime;
        proc[i].turnaroundTime = proc[i].waitingTime + proc[i].burstTime;
    }

    // Calculate total waiting and turnaround times
    for (int i = 0; i < n; i++) {
        totalWaitingTime += proc[i].waitingTime;
        totalTurnaroundTime += proc[i].turnaroundTime;
    }

    // Calculate and display average waiting and turnaround times
    float avgWaitingTime = (float)totalWaitingTime / n;
    float avgTurnaroundTime = (float)totalTurnaroundTime / n;

    printf("\nProcess ID\tBurst Time\tPriority\tWaiting Time\tTurnaround Time\n");
    for (int i = 0; i < n; i++) {
        printf("%d\t\t%d\t\t%d\t\t%d\t\t%d\n", proc[i].id, proc[i].burstTime, proc[i].priority, proc[i].waitingTime, proc[i].turnaroundTime);
    }

    printf("\nAverage Waiting Time: %.2f", avgWaitingTime);
    printf("\nAverage Turnaround Time: %.2f\n", avgTurnaroundTime);
}

int main() {
    int n;

    // Accept the number of processes
    printf("Enter the number of processes: ");
    scanf("%d", &n);

    struct Process proc[n];

    // Accept process details (ID, burst time, and priority)
    for (int i = 0; i < n; i++) {
        printf("Enter Burst Time and Priority for Process %d: ", i + 1);
        proc[i].id = i + 1;
        scanf("%d %d", &proc[i].burstTime, &proc[i].priority);
    }

    // Sort processes by priority
    sortByPriority(proc, n);

    // Calculate waiting time and turnaround time
    calculateTimes(proc, n);

    return 0;
}
