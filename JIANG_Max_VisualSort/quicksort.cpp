#include "quicksort.h"

void quicksort(vector<int> &in, int high, int low) {

    if (low < high) {
        int split = doPartition(in, high, low);
        quicksort(in, split, low);
        quicksort(in, high, split + 1);
    }

}

int doPartition(vector<int> &in, int high, int low) {

    int pivot = in[(low + high) / 2],
        i = low - 1, j = high + 1,
        temp;
    while (true) {
        do {
            i++;
        } while (in[i] < pivot);
        do {
            j--;
        } while (in[j] > pivot);
        if (i >= j) {
            return j;
        }
        temp = in[i];
        in[i] = in[j];
        in[j] = temp;
        al_clear_to_color(BLACK);
        al_draw_filled_circle(SW / 2, SH / 2, 150, YELLOW);
        drawGraph(in);
        al_flip_display();
    }

}
