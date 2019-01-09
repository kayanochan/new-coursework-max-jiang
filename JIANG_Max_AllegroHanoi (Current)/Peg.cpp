#include "Peg.h"
#include <vector>
#include <algorithm>
using namespace std;

// Constructor and destructor
Peg::Peg() {

}

Peg::~Peg() {

}

// Push and pop
void Peg::push(int n) {

    nums.push_back(n);

}

int Peg::pop() {

    // If there is nothing to pop -1 is returned
    int out = -1;

    if (nums.size()) {

        out = nums[nums.size()-1];
        nums.pop_back();

    }

    return out;

}

// Get peg length or height
int Peg::length() const {

    return nums.size();

}

// Get the top ring
int Peg::getTop() {

    int out = 0;

    if (length()) {
        out = pop();
        push(out);
    }

    return out;

}

// Get the vector of rings
vector<int> Peg::getDisk() const {

    return nums;

}

// Search peg for ring of certain size
bool Peg::hasInt(int n) const {

    bool out = false;
    if (find(nums.begin(), nums.end(), n) != nums.end())

        out = true;

    return out;
}

// Reset peg
void Peg::toEmpty() {

    nums.clear();

}
