#include <iostream>
#include <vector>
using namespace std;

/*
Create a class that initializes with a list of numbers and has one method called sum. sum should take in two parameters,
start_idx and end_idx and return the sum of the list from start_idx (inclusive) to end_idx (exclusive).

You should optimize for the sum method.
*/

/* APPROACH 1: Keep total sum and arrays tracking sum of l and r subarrays at each point. O(N) space, sum() is O(1) */
class FastListSum {
public:
    // totalSum = sum of all elements in list
    int totalSum;
    // sumL[i] = sum list[0, i)
    vector<int> sumL;
    // sumR[i] = sum list(i, r]
    vector<int> sumR;

    FastListSum(vector<int> list) {
        int n = list.size();
        sumL = vector<int>(n);
        int l = 0;
        sumR = vector<int>(n);
        int r = 0;
        for (int i = 0; i < n; i++) {
            sumL[i] = l;
            l += list[i];
            sumR[n-i-1] = r;
            r += list[n-i-1];
        }
        totalSum = l;
    }

    int sum(int start, int end) {
        int l = sumL[start];
        int r = sumR[end];
        return totalSum - l - r;
    }
};

int main(int argc, char **argv) {
    vector<int> test = {1, 2, 3, 4, 5, 6, 7};
    FastListSum list(test);
    std::cout << list.sum(1, 4) << '\n';
    return 0;
}
