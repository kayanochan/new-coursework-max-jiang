#include <iostream>
#include "quicksort.h"
using namespace std;

int main() {

    vector<int> l;
    for (int i = 0; i < 100; i++) {
        l.push_back(i*i % 97);
    }
    for (int i = 0; i < 100; i++) {
        cout << l[i] << endl;
    }
    quicksort(l, l.size() - 1);
    for (int i = 0; i < 100; i++) {
        cout << l[i] << endl;
    }


}
