#include <iostream>
#include <vector>
using namespace std;

/*
Given an array of heights, determine whether the array forms a "mountain" pattern. A mountain
pattern goes up and then down.
*/

/*
QUESTIONS:
-would [1, 1, 1] work or must have one strictly increasing/decreasing portion? Will assume does
not need to be strictly incr/decr
*/

/* APPROACH 1: state machine. O(N) */
bool isMountain(vector<int> arr) {
    int n = arr.size();
    if (n < 3) return false;
    bool start = true;
    bool isIncreasing = true;
    for (int i = 0; i < n - 1; i++) {
        if (arr[i] < arr[i + 1]) {
            if (!isIncreasing) return false;
            start = false;
        } else if (arr[i] > arr[i + 1]) {
            if (start) {
                return false;
            } else if (isIncreasing) {
                isIncreasing = false;
            }
        } else return false;
    }
    return !isIncreasing;
}

int main(int argc, char **argv) {
    vector<int> arr = {1, 2, 3, 4, 5, 4, 3, 2, 1};
    cout << isMountain(arr) << '\n';
    return 0;
}