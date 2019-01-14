#include "selectionsort.h"

void selectionsort(vector<int> &in) {

    int minInd = 0, small = in[0], temp;
    for (int i = 0; i < in.size(); i++) {
        minInd = i;
        small = in[i];
        for (int j = i + 1; j < in.size(); j++) {
            if (in[j] < small) {
                minInd = j;
                small = in[j];
            }
        }
        if (minInd != i) {
            temp = in[i];
            in[i] = in[minInd];
            in[minInd] = temp;
            al_clear_to_color(BLACK);
            al_draw_filled_circle(SW / 2, SH / 2, 150, YELLOW);
            drawGraph(in);
            al_flip_display();
        }
    }

}

