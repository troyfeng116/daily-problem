#include <iostream>
#include <vector>
using namespace std;

/*
You are given an array of intervals - that is, an array of tuples (start, 
end). The array may not be sorted, and could contain overlapping intervals. 
Return another array where the overlapping intervals are merged.

For example:
[(1, 3), (5, 8), (4, 10), (20, 25)]

This input should return [(1, 3), (4, 10), (20, 25)] since (5, 8) and 
(4, 10) can be merged into (4, 10).
*/

/*
APPROACH 1: Sort the intervals, and then merge overlapping ones. Sort takes
O(N log N), and merging should take O(N), for total O(N log N) time and O(N)
space.
*/
int myCompare(pair <int,int> a, pair <int,int> b) {
    if (a.first < b.first) return -1;
    if (a.first > b.first) return 1;
    if (a.second < b.second) return -1;
    if (a.second > b.second) return 1;
    return 0;
}
void sort(pair <int,int> *arr, int l, int r) {
    if (l >= r) return;
    pair <int,int> splitter = arr[r];
    int m = l;
    for (int i = l; i < r; i++) {
        if (myCompare(arr[i], splitter) < 0) {
            pair <int,int> temp = arr[i];
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
vector<pair <int,int> > mergeOverlap(pair <int,int> *intervals, int n) {
    sort(intervals, 0, n-1);
    vector<pair <int,int> > ans;
    int start = intervals[0].first;
    int end = intervals[0].second;
    int i = 1;
    while (i < n) {
        while (i < n && intervals[i].first < end) {
            end = max(end, intervals[i].second);
            i++;
        }
        pair<int,int> newPair;
        newPair.first = start; newPair.second = end;
        ans.push_back(newPair);
        if (i < n) {
            start = intervals[i].first;
            end = intervals[i].second;
        }
        i++;
    }
    pair<int,int> newPair;
    newPair.first = start; newPair.second = end;
    ans.push_back(newPair);
    return ans;
}

int main(int argc, char **argv) {
    int n = 7;
    pair<int,int> *test = new pair<int,int>[n];
    pair<int,int> p0; p0.first = 40; p0.second = 41;
    pair<int,int> p1; p1.first = 5; p1.second = 8;
    pair<int,int> p2; p2.first = 4; p2.second = 10;
    pair<int,int> p3; p3.first = 20; p3.second = 30;
    pair<int,int> p4; p4.first = 1; p4.second = 25;
    pair<int,int> p5; p5.first = 0; p5.second = 2;
    pair<int,int> p6; p6.first = 5; p6.second = 11;
    test[0] = p0; test[1] = p1; test[2] = p2; test[3] = p3;
    test[4] = p4; test[5] = p5; test[6] = p6;
    vector<pair<int,int> > result = mergeOverlap(test, n);
    for (int i = 0; i < result.size(); i++) {
        std::cout << result[i].first << " " << result[i].second << '\n';
    }
    return 0;
}
