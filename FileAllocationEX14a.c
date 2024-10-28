#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_BLOCKS 100

struct Block {
    int flag;  // 0 if free, 1 if allocated
};

// Function to allocate blocks sequentially for each file
void allocateSequential(int numFiles, int fileSizes[], struct Block blocks[]) {
    int i, j, start, allocatedBlocks[numFiles][MAX_BLOCKS];
    for (i = 0; i < numFiles; i++) {
        while (1) {
            start = rand() % MAX_BLOCKS;
            for (j = 0; j < fileSizes[i] && start + j < MAX_BLOCKS && blocks[start + j].flag == 0; j++);
            if (j == fileSizes[i]) break;
        }
        printf("File %d (Size: %d blocks): ", i + 1, fileSizes[i]);
        for (j = 0; j < fileSizes[i]; j++) {
            blocks[start + j].flag = 1;
            allocatedBlocks[i][j] = start + j;
            printf("%d ", allocatedBlocks[i][j]);
        }
        printf("\n");
    }
}

int main() {
    srand(time(0));  // Initialize random seed
    int numFiles;
    printf("Enter the number of files: ");
    scanf("%d", &numFiles);

    int fileSizes[numFiles];
    struct Block blocks[MAX_BLOCKS] = {0};
    for (int i = 0; i < numFiles; i++) {
        printf("Enter memory requirement for file %d: ", i + 1);
        scanf("%d", &fileSizes[i]);
    }

    allocateSequential(numFiles, fileSizes, blocks);
    return 0;
}
