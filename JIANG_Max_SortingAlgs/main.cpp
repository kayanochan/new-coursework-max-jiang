#include <fstream>
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

void bubblesort(vector<int> &in);
void insertionsort(vector<int> &in);
void selectionsort(vector<int> &in);
int binarysearch(vector<int> in, int a);
vector<int> sleepsort(vector<int> in);

int main() {

    ifstream inFile("data.txt");
    int n, temp;
    inFile >> n;
    vector <int> l;
    for (int i = 0; i < n; i++) {
        inFile >> temp;
        l.push_back(temp);
    }

    vector<int> newList = sleepsort(l);

    for (int i = 0; i < n; i++) {
        cout << newList[i] << 'a';
    }

    return 0;

}

void bubblesort(vector<int> &in) {

    int index, temp, change = 1;
    while (change) {
        change = 0;
        for (int i = 0; i < in.size() - 1; i++) {
            if (in[i] > in[i+1]) {
                temp = in[i];
                in[i] = in[i+1];
                in[i+1] = temp;
                change = 1;
            }
        }
    }

}

vector<int> sleepsort(vector<int> in) {

    vector<int> out, timer(in.size(), 0);

    while (out.size() < in.size()) {
        for (int i = 0; i < in.size(); i++) {
            timer[i]++;
            if (timer[i] == in[i]) {
                out.push_back(in[i]);
            }
        }
    }

    return out;

}

void insertionsort(vector<int> &in) {

    vector<int> sub;

    for (int i = 1; i < in.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (in[i] < in[j]) {
                sub.clear();
                for (int k = j; k < i; k++) {
                    sub.push_back(in[k]);
                }
                in[j] = in[i];
                for (int k = 0; k < sub.size(); k++) {
                    in[j+k+1] = sub[k];
                }
            }
        }
    }

}

void selectionsort(vector<int> &in) {

    int currMin, minInd, temp;

    for (int i = 0; i < in.size(); i++) {
        currMin = in[i];
        minInd = i;
        for (int j = i + 1; j < in.size(); j++) {
            if (in[j] < currMin) {
                currMin = in[j];
                minInd = j;
            }
        }
        temp = in[i];
        in[i] = in[minInd];
        in[minInd] = temp;
    }

}

int binarysearch(vector<int> in, int a) {

    int index = in.size() / 2, s = 4;

    while (in[index] != a && index >= 0 && index <= in.size()) {
        if (in[index] > a) {
            index -= max((int)in.size() / s, 1);
        }
        else {
            index += max((int)in.size() / s, 1);

        }
        s *= 2;
    }

    return index;

}
