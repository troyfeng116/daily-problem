#include <iostream>
#include <vector>
using namespace std;

/*
You are given an array of integers. Return the length of the longest increasing subsequence 
(not necessarily contiguous) in the array.

Example:
[0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15]

The following input should return 6 since the longest increasing subsequence is 
0, 2, 6, 9 , 11, 15.
*/

/* QUESTIONS: if duplicates, strictly increasing? Will assume yes */

/* APPROACH 1: Recursion. Given arr, index, curLength, and curMax, try to extend: if can't
leq curMax, continue. If greater, either include or don't. Exponential runtime. */
int recurse(vector<int> arr, int curIndex, int curLength, int curMax) {
    if (curIndex >= arr.size()) return curLength;
    if (arr[curIndex] <= curMax) return recurse(arr, curIndex+1, curLength, curMax);
    return max(recurse(arr, curIndex+1, curLength+1, arr[curIndex]),
        recurse(arr, curIndex+1, curLength, curMax));
}
int longestIncSubseq(vector<int> arr) {
    return recurse(arr, 0, 0, INT_MIN);
}

/* APPROACH 2: DP. We're definitely doing more recursive calls than we need: for example we
can store the max subseq length ending at each point in array. O(N^2) time and O(N) space */
int longestIncSubseq2(vector<int> arr) {
    vector<int> maxEndingHere(arr.size(), 1);
    for (int i = 0; i < arr.size(); i++) {
        for (int j = 0; j < i; j++) {
            if (arr[j] < arr[i]) {
                maxEndingHere[i] = max(maxEndingHere[i], maxEndingHere[j] + 1);
            }
        }
    }
    int ans = 1;
    for (int i = 0; i < maxEndingHere.size(); i++) ans = max(ans, maxEndingHere[i]);
    return ans;
}

/* APPROACH 3: There is a clever O(N log N solution). */

int main(int argc, char **argv) {
    vector<int> arr = {0, 8, 4, 12, 2, 10, 6, 14, 1, 9, 5, 13, 3, 11, 7, 15};
    int res1 = longestIncSubseq(arr);
    std::cout << res1 << '\n';
    int res2 = longestIncSubseq2(arr);
    std::cout << res2 << '\n';
    return 0;
}
