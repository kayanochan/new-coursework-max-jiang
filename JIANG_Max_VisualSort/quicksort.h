#ifndef _QUICKSORT_H
#define _QUICKSORT_H

#include "functions.h"

void quicksort(vector<int> &in, int high, int low = 0);
int doPartition(vector<int> &in, int high, int low = 0);

#endif // _QUICKSORT_H
