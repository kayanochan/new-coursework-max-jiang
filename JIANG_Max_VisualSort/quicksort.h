#ifndef _QUICKSORT_H
#define _QUICKSORT_H

#include "functions.h"

void quicksort(vector<int> &in, int high, int low, ALLEGRO_FONT *font, int &compares, int &swaps);
int doPartition(vector<int> &in, int high, int low, ALLEGRO_FONT *font, int &compares, int &swaps);

#endif // _QUICKSORT_H
