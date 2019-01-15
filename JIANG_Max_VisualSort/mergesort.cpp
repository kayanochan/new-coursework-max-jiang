#include "mergesort.h"

vector<int> mergesort(vector<int> &in, int start, int finish) {

    if (finish - start <= 1) {
        return in;
    }
    else {
        vector <int> sub1 = mergesort(in, start, (start+finish)/2),
                     sub2 = mergesort(in, (start+finish)/2, finish);
        int index1 = start, index2 = (start+finish)/2;
        for (int i = 0; i < finish - start; i++) {
            if ((sub1[index1] < sub2[index2] && index1 < (start+finish)/2) ||
                 !(index2 < finish)) {
                in[start + i] = sub1[index1];
                index1++;
            }
            else {
                in[start + i] = sub2[index2];
                index2++;
            }
        }
        al_clear_to_color(BLACK);
        al_draw_filled_circle(SW / 2, SH / 2, 150, YELLOW);
        drawGraph(in);
        al_flip_display();
        return in;
    }

}
