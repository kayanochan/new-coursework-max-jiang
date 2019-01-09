#include <iostream>
#include <stdlib.h>
#include <time.h>
using namespace std;

int cardRoulette(int choice);

int main() {
    srand(time(0));
    int choice[4];
    for (int i = 0; i < 4; i++) {
        choice[i] = 0;
    }
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 10000000; j++) {
            choice[i] += cardRoulette(i);
        }
        cout << (float)choice[i] / 10000000 << endl;
    }
    cout << (float)(choice[0] + choice[1] + choice[2]) / 30000000 << endl;
    return 0;

}

int cardRoulette(int choice) {

    int card = rand() % 52, out = 0;

    switch(choice) {
    case 0:
        if (card < 48 && card % 2) {
            out = 2;
        }
        break;
    case 1:
        if (card < 48 && !(card % 3)) {
            out = 3;
        }
        break;
    case 2:
        if (card < 48 && !(card % 4)) {
            out = 4;
        }
        break;
    default:
       if (card < 48 && !(card % 12)) {
            out = 10;
        }
    }
    return out;
}
