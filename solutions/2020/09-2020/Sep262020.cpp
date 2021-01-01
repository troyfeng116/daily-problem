#include <iostream>
#include <vector>
using namespace std;

/*
You are given an array of tuples (start, end) representing time intervals 
for lectures. The intervals may be overlapping. Return the number of rooms 
that are required.

For example. [(30, 75), (0, 50), (60, 150)] should return 2.
*/

/* HEAP FUNCTIONS */
void heapifyParent(vector<int> &minHeap, int i) {
    if (i == 0) return;
    int parent = (i-1)/2;
    if (minHeap[parent] > minHeap[i]) {
        int temp = minHeap[parent];
        minHeap[parent] = minHeap[i];
        minHeap[i] = temp;
        heapifyParent(minHeap, parent);
    }
}
void push_heap(vector<int> &minHeap, int x) {
    minHeap.push_back(x);
    heapifyParent(minHeap, minHeap.size()-1);
}
void heapifyChildren(vector<int> &minHeap, int i) {
    int minIndex = i;
    int lChild = 2*i+1;
    int rChild = 2*i+2;
    if (lChild < minHeap.size() && minHeap[lChild] < minHeap[minIndex]) {
        minIndex = lChild;
    }
    if (rChild < minHeap.size() && minHeap[rChild] < minHeap[minIndex]) {
        minIndex = rChild;
    }
    if (minIndex != i) {
        int temp = minHeap[minIndex];
        minHeap[minIndex] = minHeap[i];
        minHeap[i] = temp;
        heapifyChildren(minHeap, minIndex);
    }
}
int pop_heap(vector<int> &minHeap) {
    int ans = minHeap[0];
    minHeap[0] = minHeap[minHeap.size()-1];
    minHeap.pop_back();
    heapifyChildren(minHeap, 0);
    return ans;
}

/* APPROACH 1: Sort intervals and then store min end times in a min
heap. Time O(N log N), space O(N) */
int compare(vector<int> a, vector<int> b) {
    if (a[0] > b[0]) return 1;
    if (a[0] < b[0]) return -1;
    if (a[1] > b[1]) return 1;
    if (a[1] < b[1]) return -1;
    return 0;
}
void sort(vector<vector<int> > &intervals, int l, int r) {
    if (l >= r) return;
    vector<int> splitter = intervals[r];
    int m = l;
    for (int i = l; i < r; i++) {
        if (compare(intervals[i], splitter) < 0) {
            vector<int> temp = intervals[i];
            intervals[i] = intervals[m];
            intervals[m] = temp;
            m++;
        }
    }
    intervals[r] = intervals[m];
    intervals[m] = splitter;
    sort(intervals, l, m-1);
    sort(intervals, m+1, r);
}
int minRooms(vector<vector<int> > &intervals) {
    sort(intervals, 0, intervals.size()-1);
    vector<int> minHeap;
    int count = 0;
    for (int i = 0; i < intervals.size(); i++) {
        if (minHeap.size() == 0) {
            count++;
        }
        else {
            /* If startTime after earliest end time, reuse that room. */
            if (intervals[i][0] >= minHeap[0]) {
                std::cout << "Reuse for class " << i << '\n';
                pop_heap(minHeap);
            }
            /* Else use a new room. */
            else count++;
        }
        push_heap(minHeap, intervals[i][1]);
    }
    return count;
}

int main(int argc, char **argv) {
    vector<vector<int> > intervals = {{30, 75}, {0, 50}, {60, 150}};
    std::cout << minRooms(intervals) << '\n';
    return 0;
}
