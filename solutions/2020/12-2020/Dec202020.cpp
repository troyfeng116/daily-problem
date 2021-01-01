#include <iostream>
#include <vector>
using namespace std;

/*
Given an array and an integer k, rotate the array by k spaces. Do this without generating a new array and
without using extra space.

ex.
rotate [1, 2, 3, 4, 5] by 2 => [3, 4, 5, 1, 2]
*/

void print(vector<int> arr) {
    std::cout << '[';
    for (int i = 0; i < arr.size() - 1; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[arr.size()-1] << "]\n";
}

/* APPROACH 1: Reverse the array (in-place), reverse the first n-k elements and last k elements. */
void rotateK(vector<int> &arr, int k) {
    int n = arr.size();
    k = k % n;
    for (int i = 0; i < n/2; i++) {
        int temp = arr[i];
        arr[i] = arr[n-i-1];
        arr[n-i-1] = temp;
    }
    for (int i = 0; i < (n-k)/2; i++) {
        int temp = arr[i];
        arr[i] = arr[n-k-i-1];
        arr[n-k-i-1] = temp;
    }
    for (int i = n-k; i < (n+n-k)/2; i++) {
        int temp = arr[i];
        arr[i] = arr[n-i+n-k-1];
        arr[n-i+n-k-1] = temp;
    }
}

/* APPROACH 2: Cyclic swapping. Repeatedly place i'th element in its correct position, at
j = (i-k+n) % n. Store element at j in temp -> prev to be placed next round. If cycle
reached, increment start of cycle. Track count of elements placed and stop when count = n.
O(N) since each element is visited once. */
void rotateK2(vector<int> &arr, int k) {
    int n = arr.size();
    k = k % n;
    int count = 0;
    for (int start = 0; count < n; start++) {
        int i = start;
        int prev = arr[i];
        do {
            int j = (i-k+n) % n;
            int temp = arr[j];
            arr[j] = prev;
            prev = temp;
            i = j;
            count++;
        } while (i != start);
    }
}

int main(int argc, char **argv) {
    int k = 3;

    vector<int> arr1 = {1, 2, 3, 4, 5};
    rotateK(arr1, k);
    std::cout << "APPROACH 1 TESTING: ";
    print(arr1);

    vector<int> arr2 = {1, 2, 3, 4, 5};
    rotateK2(arr2, k);
    std::cout << "APPROACH 2 TESTING: ";
    print(arr2);
    return 0;
}
