#include <iostream>
#include <vector>
using namespace std;

/*
Given a list of numbers, find the smallest window to sort such that the whole list will be sorted. If the 
list is already sorted return (0, 0). You can assume there will be no duplicate numbers.

Example:
Input: [2, 4, 7, 5, 6, 8, 9]
Output: (2, 4)
Explanation: Sorting the window (2, 4) which is [7, 5, 6] will also means that the whole list is sorted.
*/

/* APPROACH 1: Sort and find first and last indices at which arrays differ. O(N log N) */
pair<int, int> findWindowToSort(vector<int> arr) {
    int n = arr.size();
    vector<int> arr2(n);
    for (int i = 0; i < n; i++) {
        arr2[i] = arr[i];
    }
    sort(arr2.begin(), arr2.end());
    int l = 0, r = n-1;
    while (r >= 0 && arr[r] == arr2[r]) r--;
    if (r < 0) return {0, 0};
    while (l < n && arr[l] == arr2[l]) l++;
    return {l, r};
}

/* APPROACH 2: First first and last spots in arr that are unsorted. Then find smallest and largest elements
between those points and find where they should be in arr. O(N) */
pair<int, int> findWindowToSort2(vector<int> arr) {
    int n = arr.size();
    int r = n-1;
    while (r > 0 && arr[r] >= arr[r-1]) r--;
    if (r <= 0) return {0, 0};
    int l = 0;
    while (l < n-1 && arr[l] <= arr[l+1]) l++;
    int minUnsorted = arr[l], maxUnsorted = arr[l];
    for (int i = l+1; i <= r; i++) {
        minUnsorted = min(arr[i], minUnsorted);
        maxUnsorted = max(arr[i], maxUnsorted);
    }
    l = 0;
    while (arr[l] < minUnsorted) l++;
    r = n-1;
    while (arr[r] > maxUnsorted) r--;
    return {l, r};
}

int main(int argc, char **argv) {
    vector<int> arr = {2, 4, 7, 5, 6, 8, 9};
    pair<int, int> res1 = findWindowToSort(arr);
    std::cout << "APPROACH 1 TESTING: " << res1.first << ", " << res1.second << '\n';

    pair<int, int> res2 = findWindowToSort2(arr);
    std::cout << "APPROACH 2 TESTING: " << res2.first << ", " << res2.second << '\n';
    return 0;
}
