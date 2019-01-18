#include "selectionsort.h"

void selectionsort(vector<int> &in, ALLEGRO_FONT *font, int &compares, int &swaps) {

    int minInd = 0, small = in[0], temp;
    for (int i = 0; i < in.size(); i++) {
        minInd = i;
        small = in[i];
        for (int j = i + 1; j < in.size(); j++) {
            if (in[j] < small) {
                minInd = j;
                small = in[j];
            }
            compares++;
        }
        if (minInd != i) {
            temp = in[i];
            in[i] = in[minInd];
            in[minInd] = temp;
            swaps++;
            drawGraph(in, font, compares, swaps);
        }
    }

}

