#ifndef _FUNCTIONS_H
#define _FUNCTIONS_H

#include "allegro_ini.h"

void drawGraph(const vector<int> &in, ALLEGRO_FONT *font, int compares = 0, int swaps = 0);
void scramble(vector<int> &in, ALLEGRO_FONT *font);
void changeSize(vector<int> &in, ALLEGRO_FONT *font,
                ALLEGRO_EVENT_QUEUE *event_queue, ALLEGRO_EVENT &ev);

#endif // _FUNCTIONS_H

