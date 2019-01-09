#ifndef _PEG_H
#define _PEG_H
#include <vector>
using namespace std;

class Peg {

    private:

        vector<int> nums;

    public:

        // Constructor and destructor
        Peg();
        ~Peg();

        // Push and pop
        void push(int n);
        int pop();

        // Accessors
        int getTop();
        vector<int> getDisk() const;
        int length() const;
        bool hasInt(int n) const;

        // Modifier
        void toEmpty();

};

#endif // _PEG_H
