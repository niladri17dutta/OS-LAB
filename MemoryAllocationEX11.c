#include <stdio.h>

void allocateMemory(int blockSize[], int blocks, int processSize[], int processes, char method) {
    int allocation[processes], i, j;

    // Initialize allocation to -1 (not allocated)
    for (i = 0; i < processes; i++) allocation[i] = -1;

    // Memory allocation logic
    for (i = 0; i < processes; i++) {
        int idx = -1;
        for (j = 0; j < blocks; j++) {
            if (blockSize[j] >= processSize[i]) {
                if (method == 'F' || (method == 'B' && (idx == -1 || blockSize[j] < blockSize[idx])) ||
                    (method == 'W' && (idx == -1 || blockSize[j] > blockSize[idx]))) {
                    idx = j;
                }
            }
        }
        if (idx != -1) {
            allocation[i] = idx;
            blockSize[idx] -= processSize[i];
        }
    }

    // Print the allocation result
    const char *fitType = method == 'F' ? "First" : method == 'B' ? "Best" : "Worst";
    printf("\n%s Fit Allocation:\nProcess No.\tProcess Size\tBlock No.\n", fitType);
    for (i = 0; i < processes; i++) {
        printf("%d\t\t%d\t\t%s\n", i + 1, processSize[i], allocation[i] != -1 ? blockSize[allocation[i]] + processSize[i] : "Not Allocated");
    }
}

int main() {
    int blocks, processes;
    
    // Input block and process details
    printf("Enter number of blocks and processes: ");
    scanf("%d %d", &blocks, &processes);

    int blockSize[blocks], processSize[processes], originalBlockSize[blocks];
    printf("Enter block sizes: ");
    for (int i = 0; i < blocks; i++) scanf("%d", &blockSize[i]);

    printf("Enter process sizes: ");
    for (int i = 0; i < processes; i++) scanf("%d", &processSize[i]);

    // Copy block sizes for reuse
    for (int i = 0; i < blocks; i++) originalBlockSize[i] = blockSize[i];

    // Simulate different memory allocation strategies
    allocateMemory(blockSize, blocks, processSize, processes, 'F'); // First Fit
    for (int i = 0; i < blocks; i++) blockSize[i] = originalBlockSize[i]; // Restore block sizes

    allocateMemory(blockSize, blocks, processSize, processes, 'B'); // Best Fit
    for (int i = 0; i < blocks; i++) blockSize[i] = originalBlockSize[i]; // Restore block sizes

    allocateMemory(blockSize, blocks, processSize, processes, 'W'); // Worst Fit

    return 0;
}
