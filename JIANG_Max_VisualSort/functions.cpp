#include "functions.h"

void drawGraph(const vector<int> &in, ALLEGRO_FONT *font, int compares, int swaps) {

    al_clear_to_color(BLACK);

    int big = in[0];
    for (int i = 1; i < in.size(); i++) {
        big = max(in[i], big);
    }

    for (int i = 0; i < in.size(); i++) {
        al_draw_filled_rectangle(100+(SW-200)/in.size()*i, SH-50-(SH-100)*(float)in[i]/big,
                                 100+(SW-200)/in.size()*(i+1), SH-50, GREY);
    }

    al_draw_textf(font, WHITE, SW / 3, SH - 50,
                  ALLEGRO_ALIGN_CENTER, "%d comparison(s)", compares);
    al_draw_textf(font, WHITE, 2 * SW / 3, SH - 50,
                  ALLEGRO_ALIGN_CENTER, "%d swap(s)", swaps);

    al_flip_display();

}

void scramble(vector<int> &in, ALLEGRO_FONT *font) {

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
    drawGraph(in, font);
}
