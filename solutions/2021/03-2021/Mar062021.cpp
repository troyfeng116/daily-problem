#include <iostream>
#include <vector>
using namespace std;

/*
Given an array of numbers, determine whether it can be partitioned into 3 arrays of equal sums.

ex.
[0, 2, 1, -6, 6, -7, 9, 1, 2, 0, 1] can be partitioned into:
[0, 2, 1], [-6, 6, -7, 9, 1], [2, 0, 1], all of which sum to 3.
*/

/* QUESTIONS: subarrays must be contiguous? Will assume yes */

/* APPROACH 1: find total sum of elements in array. Each partitioned array must add to sum / 3.
First, iterate from left. If subset adds to target, move right pointer to the left until target
found. Else, return false.
O(N) */
bool canPartitionIntoThree(vector<int> arr) {
    int n = arr.size();
    int totalSum = 0;
    for (int i = 0; i < n; i++) {
        totalSum += arr[i];
    }
    if (totalSum % 3 != 0) return false;
    int lSum = arr[0], rSum = arr[n - 1];
    int l = 1, r = n - 2;
    while (l < r) {
        if (lSum == totalSum / 3) {
            while (l < r) {
                if (rSum == totalSum / 3) {
                    printf("Partition indices: [0,%d], [%d,%d], [%d, %d]\n", l - 1, l, r, r + 1, n - 1);
                    return true;
                }
                rSum += arr[r];
                r--;
            }
            return false;
        }
        lSum += arr[l];
        l++;
    }
    return false;
}

int main(int argc, char **argv) {
    vector<int> test = {0, 2, 1, -6, 6, -7, 9, 1, 2, 0, 1};
    cout << canPartitionIntoThree(test) << '\n';
    return 0;
}
