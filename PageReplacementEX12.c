#include <stdio.h>

#define MAX_FRAMES 10
#define MAX_PAGES 100

// FIFO Page Replacement
void FIFO(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], pageFaults = 0, k = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1; // Initialize frames
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) if (frame[j] == pages[i]) found = 1; // Check if page is in frame
        if (!found) {
            frame[k] = pages[i]; // Replace oldest page
            k = (k + 1) % frames;
            pageFaults++;
        }
    }
    printf("Page Faults (FIFO): %d\n", pageFaults);
}

// LRU Page Replacement
void LRU(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], timestamp[MAX_FRAMES], pageFaults = 0, time = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1; // Initialize frames
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) if (frame[j] == pages[i]) { found = 1; timestamp[j] = time++; } // Update usage timestamp
        if (!found) {
            int lruIndex = 0;
            for (int j = 1; j < frames; j++) if (timestamp[j] < timestamp[lruIndex]) lruIndex = j; // Find least recently used page
            frame[lruIndex] = pages[i];
            timestamp[lruIndex] = time++;
            pageFaults++;
        }
    }
    printf("Page Faults (LRU): %d\n", pageFaults);
}

// LFU Page Replacement
void LFU(int pages[], int n, int frames) {
    int frame[MAX_FRAMES], freq[MAX_FRAMES] = {0}, pageFaults = 0;
    for (int i = 0; i < frames; i++) frame[i] = -1; // Initialize frames
    for (int i = 0; i < n; i++) {
        int found = 0;
        for (int j = 0; j < frames; j++) if (frame[j] == pages[i]) { found = 1; freq[j]++; } // Increment frequency count
        if (!found) {
            int lfuIndex = 0;
            for (int j = 1; j < frames; j++) if (freq[j] < freq[lfuIndex]) lfuIndex = j; // Find least frequently used page
            frame[lfuIndex] = pages[i];
            freq[lfuIndex] = 1;
            pageFaults++;
        }
    }
    printf("Page Faults (LFU): %d\n", pageFaults);
}

int main() {
    int pages[MAX_PAGES], n, frames;
    printf("Enter number of pages: ");
    scanf("%d", &n);
    printf("Enter page reference string: ");
    for (int i = 0; i < n; i++) scanf("%d", &pages[i]);
    printf("Enter number of frames: ");
    scanf("%d", &frames);

    FIFO(pages, n, frames);
    LRU(pages, n, frames);
    LFU(pages, n, frames);

    return 0;
}
