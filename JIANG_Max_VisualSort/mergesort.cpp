#include "mergesort.h"

vector<int> mergesort(vector<int> &in, int start, int finish, ALLEGRO_FONT *font, int &compares, int &swaps) {

    // Check if sub-lists are empty
    if (finish - start <= 1) {
        return in;
    }

    else {

        // Divide list, do recursive step
        vector <int> sub1 = mergesort(in, start, (start+finish)/2, font, compares, swaps),
                     sub2 = mergesort(in, (start+finish)/2, finish, font, compares, swaps);
        // Initialize variables
        int index1 = start, index2 = (start+finish)/2;

        // Merge lists
        for (int i = 0; i < finish - start; i++) {
            if ((sub1[index1] < sub2[index2] && index1 < (start + finish) / 2) ||
                 !(index2 < finish)) {
                in[start + i] = sub1[index1];
                index1++;
                compares++;
            }
            else {
                in[start + i] = sub2[index2];
                index2++;
            }
        }

        // Redraw screen
        drawGraph(in, font, compares, swaps);

        return in;

    }

}
