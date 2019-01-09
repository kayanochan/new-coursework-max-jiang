#ifndef _QUICKSORT_H
#define _QUICKSORT_H

#include "allegro_ini.h"
#include <vector>
using namespace std;

void quicksort(vector<int> &in, int high, int low = 0);
int doPartition(vector<int> &in, int high, int low = 0);

#endif // _QUICKSORT_H
