#include <iostream>
#include <vector>
using namespace std;

/*
Given a sorted list of size n, with m unique elements (thus m < n), modify the list such that the first
m unique elements in the list will be sorted, ignoring the rest of the list. Your solution should have a 
space complexity of O(1). Instead of returning the list (since you are just modifying the original list),
you should return what m is.

ex.
arr = [1, 1, 2, 3, 4, 4, 4, 4, 4, 5, 5, 6, 7, 9] => m = 8, first 8 should be [1, 2, 3, 4, 5, 6, 7, 9]
*/

void print(vector<int> arr, int m) {
    if (arr.size() == 0) {
        cout << "[]\n";
        return;
    }
    cout << "[";
    for (int i = 0; i < m - 1; i++) {
        cout << arr[i] << ", ";
    }
    cout << arr[m - 1] << "]\n";
}

/* APPROACH 1: Keep index of end of sorted unique portion like quicksort partition. O(N) */
int partitionUnique(vector<int> &arr) {
    if (arr.size() == 0) return 0;
    int m = 1;
    for (int i = 1; i < arr.size(); i++) {
        if (arr[i] != arr[m - 1]) {
            int temp = arr[i];
            arr[i] = arr[m];
            arr[m] = temp;
            m++;
        }
    }
    return m;
}

int main(int argc, char **argv) {
    vector<int> arr = {1, 1, 2, 3, 4, 4, 4, 4, 4, 5, 5, 6, 7, 9};
    
    int m = partitionUnique(arr);
    cout << m << '\n';
    print(arr, m);
    return 0;
}
