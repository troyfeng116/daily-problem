#include <iostream>
#include <vector>
using namespace std;

/*
Given a sorted list with duplicates, and a target number n, find the range in which the number exists
(represented as a tuple (low, high), both inclusive. If the number does not exist in the list, return (-1, -1)).

ex.
[1, 1, 3, 5, 7], target = 1 -> (0, 1)
[1, 2, 3, 4], target = 5 -> (-1, -1)
*/

/* APPROACH 1: Binary search for first and last occurrence. O(log N) */
int findFirstOccurrence(vector<int> arr, int target) {
    int n = arr.size();
    if (target < arr[0] || arr[n - 1] < target) return -1;
    int l = 0, r = n - 1;
    while (l < r) {
        int m = (l + r) / 2;
        if (target < arr[m]) {
            r = m - 1;
        } else if (target > arr[m]) {
            l = m + 1;
        } else {
            if (m == 0 || arr[m] != arr[m - 1]) return m;
            r = m - 1;
        }
    }
    return l;
}
int findLastOccurrence(vector<int> arr, int target) {
    int n = arr.size();
    if (target < arr[0] || arr[n - 1] < target) return -1;
    int l = 0, r = n - 1;
    while (l < r) {
        int m = (l + r) / 2;
        if (target < arr[m]) {
            r = m - 1;
        } else if (target > arr[m]) {
            l = m + 1;
        } else {
            if (m == n - 1 || arr[m] != arr[m + 1]) return m;
            l = m + 1;
        }
    }
    return l;
}
pair<int, int> findRange(vector<int> arr, int target) {
    return {findFirstOccurrence(arr, target), findLastOccurrence(arr, target)};
}

int main(int argc, char **argv) {
    vector<int> test = {-2, -4, 1, 1, 1, 1, 1, 1, 3, 5, 7};
    int target = 1;
    pair<int, int> res = findRange(test, target);
    cout << "(" << res.first << ", " << res.second << ")\n";
    return 0;
}
