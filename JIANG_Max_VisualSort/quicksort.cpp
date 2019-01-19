#include "quicksort.h"

// Main quick sort function
void quicksort(vector<int> &in, int high, int low, ALLEGRO_FONT *font, int &compares, int &swaps) {

    // If the sub-lists are non-empty
    if (low < high) {

        // Do a pass to partition list
        int split = doPartition(in, high, low, font, compares, swaps);

        // Do recursize step
        quicksort(in, split, low, font, compares, swaps);
        quicksort(in, high, split + 1, font, compares, swaps);

    }

}

// Partition function
int doPartition(vector<int> &in, int high, int low, ALLEGRO_FONT *font, int &compares, int &swaps) {

    // Get pivot
    // Initialize other variables
    int pivot = in[(low + high) / 2],
        i = low - 1, j = high + 1,
        temp;

    while (true) {

        // Find element on left side that needs to switch
        do {
            i++;
            compares++;
        } while (in[i] < pivot);

        // Do the same for the right side
        do {
            j--;
            compares++;
        } while (in[j] > pivot);

        // If searches overlap, partition is done
        if (i >= j) {
            return j;
        }
        compares++;

        // Switch elements
        temp = in[i];
        in[i] = in[j];
        in[j] = temp;
        swaps++;

        // Redraw screen
        drawGraph(in, font, compares, swaps);

    }

}
