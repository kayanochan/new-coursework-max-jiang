#include <iostream>
#include "quicksort.cpp"
using namespace std;

int main() {

    vector<int> l;
    for (int i = 0; i < 10; i++) {
        l.push_back(i*i % 10);
    }
    for (int i = 0; i < 10; i++) {
        cout << l[i] << endl;
    }
    quicksort(l, l.size() - 1);
    for (int i = 0; i < 10; i++) {
        cout << l[i] << endl;
    }


}
