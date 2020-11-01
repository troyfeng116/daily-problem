#include <iostream>
#include <vector>
using namespace std;

/*
Given a list of integers, return the bounds of the minimum range that must be sorted so that the 
whole list would be sorted.

Example:
Input: [1, 7, 9, 5, 7, 8, 10]
Output: (1, 5)
Explanation:
The numbers between index 1 and 5 are out of order and need to be sorted.
*/

/* APPROACH 1: Sort and one-pass to find spots where out of order. O(N log N) tune abd
O(N) space */
void sort(vector<int> &arr, int l, int r) {
    if (l < r) {
        int splitter = arr[r];
        int m = l;
        for (int i = l; i < r; i++) {
            if (arr[i] < splitter) {
                int temp = arr[i];
                arr[i] = arr[m];
                arr[m] = temp;
                m++;
            }
        }
        arr[r] = arr[m];
        arr[m] = splitter;
        sort(arr, l, m-1);
        sort(arr, m+1, r);
    }
}
int shortestUnsortedSubarray(vector<int> arr) {
    int n = arr.size();
    vector<int> copy(arr);
    sort(copy, 0, n-1);
    int l = 0;
    while (l < n && arr[l] <= copy[l]) l++;
    int r = n-1;
    while (r >= 0 && arr[r] >= copy[r]) r--;
    std::cout << '[' << l << ", " << r << "]\n";
    return r < 0 ? 0 : r-l+1;
}

/* APPROACH 2: Find first and last inversions; say those points are at l and
r. That subarray has to be part of our shorted unsorted subarray. Within [l,r],
there is a min and max. We need to extend l and r until that min/max is in
order within that subarray. O(N) time. */
int shortestUnsortedSubarray2(vector<int> arr) {
    int n = arr.size();
    int l = 0;
    while (l < n-1 && arr[l] <= arr[l+1]) l++;
    if (l == n-1) return 0;
    int r = n-1;
    while (r > 0 && arr[r] >= arr[r-1]) r--;
    int minInWindow = INT_MAX, maxInWindow = INT_MIN;
    for (int i = l; i <= r; i++) {
        minInWindow = min(minInWindow, arr[i]);
        maxInWindow = max(maxInWindow, arr[i]);
    }
    while (l > 0 && arr[l-1] > minInWindow) l--;
    while (r < n-1 && arr[r+1] < maxInWindow) r++;
    std::cout << '[' << l << ", " << r << "]\n";
    return r-l+1;
}

int main(int argc, char **argv) {
    vector<int> test = {1, 7, 9, 5, 7, 8, 10};
    int res1 = shortestUnsortedSubarray(test);
    std::cout << res1 << '\n';
    int res2 = shortestUnsortedSubarray2(test);
    std::cout << res2 << '\n';
    return 0;
}
