#include "selectionsort.h"

void selectionsort(vector<int> &in, ALLEGRO_FONT *font, int &compares, int &swaps) {

    // Initialize variables
    int minInd = 0, small = in[0], temp;

    for (int i = 0; i < in.size(); i++) {

        // Find minimal element
        minInd = i;
        small = in[i];
        for (int j = i + 1; j < in.size(); j++) {
            if (in[j] < small) {
                minInd = j;
                small = in[j];
            }
            compares++;
        }

        // Swap into place
        if (minInd != i) {
            temp = in[i];
            in[i] = in[minInd];
            in[minInd] = temp;
            swaps++;
            // Redraw screen
            drawGraph(in, font, compares, swaps);
        }

    }

}

