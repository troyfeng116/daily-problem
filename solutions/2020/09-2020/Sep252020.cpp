#include <iostream>
#include <vector>
using namespace std;

/*
You are given a stream of numbers. Compute the median for each new element .

Eg. Given [2, 1, 4, 7, 2, 0, 5], the algorithm should output [2, 1.5, 2, 3.0, 2, 2, 2]
*/

void print(vector<int> arr) {
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i] << ' ';
    }
    std::cout << '\n';
}

/* APPROACH 1: Keep sorted array. O(N^2) time and O(N) space. */
void insert(int x, vector<int> &arr) {
    arr.push_back(x);
    int i = arr.size()-1;
    while (i > 0 && arr[i] < arr[i-1]) {
        arr[i] = arr[i-1];
        arr[i-1] = x;
        i--;
    }
}
void printMedianStream1(vector<int> arr) {
    vector<int> sorted;
    for (int i = 0; i < arr.size(); i++) {
        insert(arr[i], sorted);
        if (i%2 == 0) std::cout << sorted[i/2] << ' ';
        else std::cout << (sorted[i/2] + sorted[1+i/2])/2.0 << ' ';
    }
    std::cout << '\n';
}

/* APPROACH 2: Max and min heap. O(N) space, O(N log N) time */
void heapifyChildren(vector<int> &arr, int i, bool max) {
    int lChild = 2*i+1;
    int rChild = 2*i+2;
    if (max) {
        int maxIndex = i;
        if (lChild < arr.size() && arr[lChild] > arr[maxIndex]) maxIndex = lChild;
        if (rChild < arr.size() && arr[rChild] > arr[maxIndex]) maxIndex = rChild;
        if (maxIndex != i) {
            int temp = arr[maxIndex];
            arr[maxIndex] = arr[i];
            arr[i] = temp;
            heapifyChildren(arr, maxIndex, max);
        }
    }
    else {
        int minIndex = i;
        if (lChild < arr.size() && arr[lChild] < arr[minIndex]) minIndex = lChild;
        if (rChild < arr.size() && arr[rChild] < arr[minIndex]) minIndex = rChild;
        if (minIndex != i) {
            int temp = arr[minIndex];
            arr[minIndex] = arr[i];
            arr[i] = temp;
            heapifyChildren(arr, minIndex, max);
        }
    }
}
int popRoot(vector<int> &arr, bool max) {
    int ans = arr[0];
    arr[0] = arr[arr.size()-1];
    arr.pop_back();
    heapifyChildren(arr, 0, max);
    return ans;
}
void heapifyParent(vector<int> &arr, int i, bool max) {
    int parent = (i-1)/2;
    if ((max && arr[i] > arr[parent]) || (!max && arr[i] < arr[parent])) {
        int temp = arr[i];
        arr[i] = arr[parent];
        arr[parent] = temp;
        heapifyParent(arr, parent, max);
    }
}
void insert(vector<int> &arr, int x, bool max) {
    arr.push_back(x);
    heapifyParent(arr, arr.size()-1, max);
}
void printMedianStream2(vector<int> arr) {
    vector<int> maxHeap;
    vector<int> minHeap;
    std::cout << arr[0] << ' ';
    double median = arr[0];
    insert(maxHeap, arr[0], true);
    for (int i = 1; i < arr.size(); i++) {
        if (maxHeap.size() < minHeap.size()) {
            if (arr[i] > median) {
                insert(maxHeap, popRoot(minHeap, false), true);
                insert(minHeap, arr[i], false);
            }
            else {
                insert(maxHeap, arr[i], true);
            }
            median = (minHeap[0] + maxHeap[0])/2.0;
        }
        else if (maxHeap.size() > minHeap.size()) {
            if (arr[i] > median) {
                insert(minHeap, arr[i], false);
            }
            else {
                insert(minHeap, popRoot(maxHeap, true), false);
                insert(maxHeap, arr[i], true);
            }
            median = (minHeap[0] + maxHeap[0])/2.0;
        }
        else {
            if (arr[i] < median) {
                insert(maxHeap, arr[i], true);
                median = maxHeap[0];
            }
            else {
                insert(minHeap, arr[i], false);
                median = minHeap[0];
            }
        }
        std::cout << median << ' ';
    }
    std::cout << '\n';
}


int main(int argc, char **argv) {
    vector<int> test = {2, 1, 4, 7, 2, 0, 5};
    printMedianStream1(test);
    printMedianStream2(test);
    return 0;
}
