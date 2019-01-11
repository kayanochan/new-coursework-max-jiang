#include "functions.h"

void drawGraph(const vector<int> &in) {

    int big = in[0];
    for (int i = 1; i < in.size(); i++) {
        big = max(in[i], big);
    }

    for (int i = 0; i < in.size(); i++) {
        al_draw_filled_rectangle(100+(SW-200)/in.size()*i, SH-50-(SH-100)*(float)in[i]/big,
                                 100+(SW-200)/in.size()*(i+1), SH-50, GREY);
    }

}

void scramble(vector<int> &in) {

    vector<int> deck;
    int temp, vecSize = in.size();
    for (int i = 0; i < in.size(); i++) {
        deck.push_back(in[i]);
    }
    in.clear();
    for (int i = 0; i < vecSize; i++) {
        temp = rand() % deck.size();
        in.push_back(deck[temp]);
        deck.erase(deck.begin()+temp);
    }
}
