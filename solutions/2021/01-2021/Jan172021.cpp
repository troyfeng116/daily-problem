#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
Given a list of meetings that will happen during a day, find the minimum number of meeting
rooms that can fit all meetings.

Each meeting will be represented by a tuple of (start_time, end_time), where both start_time
and end_time will be represented by an integer to indicate the time. start_time will be
inclusive, and end_time will be exclusive, meaning a meeting of (0, 10) and (10, 20) will
only require 1 meeting room.

ex. [(20, 30), (10, 21), (0, 50)] => 3
*/

/* APPROACH 1: Min heap. Sort by start timestamp. Then iterate through, and store end
timestamps in min heap after sorting.
If earliest end time is less than next start timestamp, that room can be reused.
Remove that end time from heap and add new end time to signify that room is in use.
Else, if earliest end time is after next start time, we need a new room, as all
other rooms are currently still in session.
O(N log N) */
int myCompare(vector<int> a, vector<int> b) {
    return a[0] - b[0] != 0 ? a[0] - b[0] : a[1] - b[1];
}
void sortIntervals(vector<vector<int> > &intervals, int l, int r) {
    if (l < r) {
        vector<int> splitter = intervals[r];
        int m = l;
        for (int i = l; i < r; i++) {
            if (myCompare(intervals[i], splitter) < 0) {
                vector<int> temp = intervals[i];
                intervals[i] = intervals[m];
                intervals[m] = temp;
                m++;
            }
        }
        intervals[r] = intervals[m];
        intervals[m] = splitter;
        sortIntervals(intervals, l, m - 1);
        sortIntervals(intervals, m + 1, r);
    }
}
int roomsRequired(vector<vector<int> > intervals) {
    int n = intervals.size();
    sortIntervals(intervals, 0, n - 1);
    int count = 0;
    priority_queue<int, vector<int>, greater<int> > minHeap;
    for (int i = 0; i < intervals.size(); i++) {
        if (minHeap.empty()) {
            count++;
        } else {
            if (intervals[i][0] >= minHeap.top()) {
                minHeap.pop();
            } else count++;
        }
        minHeap.push(intervals[i][1]);
    }
    return count;
}

int main(int argc, char **argv) {
    vector<vector<int> > intervals = {{20, 30}, {10, 21}, {0, 50}, {49, 53}, {29, 55}};
    std::cout << roomsRequired(intervals) << '\n';
    return 0;
}
