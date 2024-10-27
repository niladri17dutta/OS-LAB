#include <stdio.h>
#include <stdlib.h>

// Function to implement FCFS disk scheduling
void fcfs(int req[], int n, int head) {
    int seek = 0;
    printf("FCFS:\n");
    for (int i = 0; i < n; i++) {
        seek += abs(head - req[i]);
        printf("Move from %d to %d (Seek %d)\n", head, req[i], abs(head - req[i]));
        head = req[i];
    }
    printf("Total Seek Time: %d\n", seek);
}

// Function to implement SCAN disk scheduling
void scan(int req[], int n, int head, int disk_size, int dir) {
    int seek = 0, sorted[n + 2], size = n + 2;
    for (int i = 0; i < n; i++) sorted[i] = req[i];
    sorted[n] = 0, sorted[n + 1] = disk_size - 1;
    for (int i = 0; i < size - 1; i++) for (int j = 0; j < size - i - 1; j++)
        if (sorted[j] > sorted[j + 1]) { int tmp = sorted[j]; sorted[j] = sorted[j + 1]; sorted[j + 1] = tmp; }
    int idx = 0;
    while (idx < size && head > sorted[idx]) idx++;
    printf("SCAN:\n");
    for (int i = dir ? idx : idx - 1; dir ? i < size : i >= 0; dir ? i++ : i--) {
        seek += abs(head - sorted[i]);
        printf("Move from %d to %d (Seek %d)\n", head, sorted[i], abs(head - sorted[i]));
        head = sorted[i];
    }
    printf("Total Seek Time: %d\n", seek);
}

// Function to implement C-SCAN disk scheduling
void cscan(int req[], int n, int head, int disk_size) {
    int seek = 0, sorted[n + 2], size = n + 2;
    for (int i = 0; i < n; i++) sorted[i] = req[i];
    sorted[n] = 0, sorted[n + 1] = disk_size - 1;
    for (int i = 0; i < size - 1; i++) for (int j = 0; j < size - i - 1; j++)
        if (sorted[j] > sorted[j + 1]) {
            int tmp = sorted[j];
            sorted[j] = sorted[j + 1];
            sorted[j + 1] = tmp;
        }
    int idx = 0;
    while (idx < size && head > sorted[idx]) idx++;
    printf("C-SCAN:\n");
    for (int i = idx; i < size; i++) { seek += abs(head - sorted[i]); head = sorted[i]; }
    seek += abs(head - 0);
    head = 0;
    for (int i = 0; i < idx; i++) { seek += abs(head - sorted[i]); head = sorted[i]; }
    printf("Total Seek Time: %d\n", seek);
}

int main() {
    int n, head, disk_size, choice, dir;
    printf("Enter number of requests: ");
    scanf("%d", &n);
    int req[n];
    printf("Enter the request sequence: ");
    for (int i = 0; i < n; i++) scanf("%d", &req[i]);
    printf("Enter initial head position: ");
    scanf("%d", &head);
    printf("Enter disk size: ");
    scanf("%d", &disk_size);
    while (1) {
        printf("\n1. FCFS\n2. SCAN\n3. C-SCAN\n4. Exit\nChoice: ");
        scanf("%d", &choice);
        if (choice == 4) break;
        if (choice == 1) fcfs(req, n, head);
        else if (choice == 2) {
            printf("Enter direction (1 for High, 0 for Low): ");
            scanf("%d", &dir);
            scan(req, n, head, disk_size, dir);
        } else if (choice == 3) cscan(req, n, head, disk_size);
        else printf("Invalid choice!\n");
    }
    return 0;
}
