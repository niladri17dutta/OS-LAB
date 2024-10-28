#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#define MAX_BLOCKS 100

struct Block {
    int next, flag;  // 'next' points to the next block, 'flag' is 0 if free, 1 if allocated
};

void allocateChained(int numFiles, int fileSizes[], struct Block blocks[]) {
    for (int i = 0; i < numFiles; i++) {
        int start, next;
        do { start = rand() % MAX_BLOCKS; } while (blocks[start].flag);  // Find a free start block
        blocks[start].flag = 1;
        printf("File %d (Size: %d blocks): %d", i + 1, fileSizes[i], start);
        next = start;
        for (int j = 1; j < fileSizes[i]; j++) {  // Allocate remaining blocks
            int newBlock;
            do { newBlock = rand() % MAX_BLOCKS; } while (blocks[newBlock].flag);
            blocks[next].next = newBlock;
            blocks[newBlock].flag = 1;
            next = newBlock;
            printf(" -> %d", newBlock);
        }
        blocks[next].next = -1;  // End of chain
        printf("\n");
    }
}

int main() {
    srand(time(0));
    int numFiles;
    printf("Enter the number of files: ");
    scanf("%d", &numFiles);
    int fileSizes[numFiles];
    struct Block blocks[MAX_BLOCKS] = {0};
    for (int i = 0; i < numFiles; i++) {
        printf("Enter memory requirement (blocks) for file %d: ", i + 1);
        scanf("%d", &fileSizes[i]);
    }
    allocateChained(numFiles, fileSizes, blocks);
    return 0;
}
