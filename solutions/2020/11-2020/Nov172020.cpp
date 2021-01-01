#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
You are given a list of n numbers, where every number is at most k indexes away from its properly 
sorted index. Write a sorting algorithm (that will be given the number k) for this list that can 
solve this in O(n log k).

Example:
Input: [3, 2, 6, 5, 4], k = 2
Output: [2, 3, 4, 5, 6]
As seen above, every number is at most 2 indexes away from its proper sorted index.
*/

void print(vector<int> arr) {
    std::cout << "[";
    for (int i = 0; i < arr.size()-1; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[arr.size()-1] << "]\n";
}

/* APPROACH 1: Insertion sort. O(N*K) */
void sort(vector<int> &arr, int k) {
    for (int i = 1; i < arr.size(); i++) {
        int toInsert = arr[i];
        int j = i-1;
        while (j >= 0 && toInsert < arr[j]) {
            arr[j+1] = arr[j];
            j--;
        }
        arr[j+1] = toInsert;
    }
}

/* APPROACH 2: Heap. Keep heap of k+1 elements, so that min element must be next element to push
on sorted array. O(N log K) */
void sort2(vector<int> &arr, int k) {
    priority_queue<int, vector<int>, greater<int>> heap(arr.begin(), arr.begin() + k + 1);
    int index = 0;
    for (int i = k+1; i < arr.size(); i++) {
        arr[index] = heap.top();
        heap.pop();
        heap.push(arr[i]);
        index++;
    }
    while (!heap.empty()) {
        arr[index] = heap.top();
        heap.pop();
        index++;
    }
}

int main(int argc, char **argv) {
    int k = 3;
    vector<int> arr1 = {6, 5, 3, 2, 8, 10, 9};
    sort(arr1, k);
    std::cout << "APPROACH 1 TESTING: ";
    print(arr1);

    vector<int> arr2 = {6, 5, 3, 2, 8, 10, 9};
    sort2(arr2, k);
    std::cout << "APPROACH 2 TESTING: ";
    print(arr2);
    return 0;
}
