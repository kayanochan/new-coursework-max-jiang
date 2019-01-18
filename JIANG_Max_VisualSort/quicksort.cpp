#include "quicksort.h"

void quicksort(vector<int> &in, int high, int low, ALLEGRO_FONT *font, int &compares, int &swaps) {

    if (low < high) {
        int split = doPartition(in, high, low, font, compares, swaps);
        quicksort(in, split, low, font, compares, swaps);
        quicksort(in, high, split + 1, font, compares, swaps);
    }

}

int doPartition(vector<int> &in, int high, int low, ALLEGRO_FONT *font, int &compares, int &swaps) {

    int pivot = in[(low + high) / 2],
        i = low - 1, j = high + 1,
        temp;

    while (true) {
        do {
            i++;
            compares++;
        } while (in[i] < pivot);
        do {
            j--;
            compares++;
        } while (in[j] > pivot);
        if (i >= j) {
            return j;
        }
        compares++;

        temp = in[i];
        in[i] = in[j];
        in[j] = temp;
        swaps++;

        drawGraph(in, font, compares, swaps);

    }

}
