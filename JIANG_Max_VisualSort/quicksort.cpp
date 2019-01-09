#include <vector>
using namespace std;

void quicksort(vector<int> &in, int high, int low = 0);
int doPartition(vector<int> &in, int high, int low = 0);

void quicksort(vector<int> &in, int high, int low) {

    int split = doPartition(in, high);
    quicksort(in, split);
    quicksort(in, high, split);

}

int doPartition(vector<int> &in, int high, int low) {

    int pivot = in[(low + high) / 2],
        i = low - 1, j = high + 1,
        temp;
    while (true) {
        do {
            i++;
        } while (in[i] <= pivot);
        do {
            j--;
        } while (in[j] >= pivot);
        if (i >= j) {
            return j;
        }
        temp = in[i];
        in[i] = in[j];
        in[j] = temp;
    }

}
