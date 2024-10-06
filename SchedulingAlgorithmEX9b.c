#include <stdio.h>

struct Process {
    int id;             // Process ID
    int burst_time;      // Burst Time
    int waiting_time;    // Waiting Time
    int turnaround_time; // Turnaround Time
    int remaining_time;  // Remaining Time after each time slice
};

// Function to calculate average waiting time and turnaround time using Round Robin scheduling
void round_robin(struct Process processes[], int n, int time_quantum) {
    int total_time = 0, total_waiting_time = 0, total_turnaround_time = 0;
    int completed_processes = 0;
    
    // Initialize remaining time for each process
    for (int i = 0; i < n; i++) {
        processes[i].remaining_time = processes[i].burst_time;
    }
    
    while (completed_processes < n) {
        for (int i = 0; i < n; i++) {
            if (processes[i].remaining_time > 0) {
                if (processes[i].remaining_time > time_quantum) {
                    total_time += time_quantum;
                    processes[i].remaining_time -= time_quantum;
                } else {
                    total_time += processes[i].remaining_time;
                    processes[i].waiting_time = total_time - processes[i].burst_time;
                    processes[i].turnaround_time = processes[i].waiting_time + processes[i].burst_time;
                    
                    total_waiting_time += processes[i].waiting_time;
                    total_turnaround_time += processes[i].turnaround_time;
                    
                    processes[i].remaining_time = 0; // Process completed
                    completed_processes++;
                }
            }
        }
    }

    // Calculate average waiting time and turnaround time
    printf("Average Waiting Time: %.2f\n", (float)total_waiting_time / n);
    printf("Average Turnaround Time: %.2f\n", (float)total_turnaround_time / n);
}

int main() {
    int n, time_quantum;
    
    // Input the number of processes and the time quantum
    printf("Enter the number of processes: ");
    scanf("%d", &n);
    printf("Enter the time quantum: ");
    scanf("%d", &time_quantum);
    
    struct Process processes[n];
    
    // Input burst time for each process
    for (int i = 0; i < n; i++) {
        processes[i].id = i + 1;
        printf("Enter burst time for process %d: ", processes[i].id);
        scanf("%d", &processes[i].burst_time);
    }
    
    // Call the Round Robin scheduling function
    round_robin(processes, n, time_quantum);
    
    return 0;
}
