#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
Find the k-th largest number in a sequence of unsorted numbers.

ex. [8, 7, 2, 3, 4, 1, 5, 6, 9, 0], k = 3 -> 7
*/

/* APPROACH 1: min heap. O(N log K) */
int kthLargest(vector<int> list, int k) {
    int n = list.size();
    if (k > n) {
        cout << "k = " << k << " is greater than list size " << n << '\n';
        return -1;
    }
    priority_queue<int, vector<int>, greater<int> > minHeap;
    for (int i = 0; i < k; i++) minHeap.push(list[i]);
    for (int i = k; i < n; i++) {
        if (minHeap.top() < list[i]) {
            minHeap.pop();
            minHeap.push(list[i]);
        }
    }
    return minHeap.top();
}

/* APPROACH 2: bucket sort. Assumes all elemnets positive. O(N) time, O(max element) space */
int kthLargest2(vector<int> list, int k) {
    int n = list.size();
    int maxElement = 0;
    for (int i = 0; i < n; i++) maxElement = max(list[i], maxElement);
    vector<int> buckets(maxElement + 1, 0);
    for (int i = 0; i < n; i++) buckets[list[i]]++;
    int count = 0;
    for (int el = maxElement; el >= 0; el--) {
        if (buckets[el] > 0) count += buckets[el];
        if (count >= k) return el;
    }
    cout << "k = " << k << " is greater than list size " << n << '\n';
    return -1;
}

int main(int argc, char **argv) {
    vector<int> list = {8, 7, 2, 3, 4, 1, 5, 6, 9, 0};
    int k = 3;
    cout << "APPROACH 1 TESTING: " << kthLargest(list, k) << '\n';
    cout << "APPROACH 2 TESTING: " << kthLargest2(list, k) << '\n';
    return 0;
}
