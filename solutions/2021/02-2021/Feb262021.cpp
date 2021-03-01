#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
Given a list of points and a number k, find the k closest points to the origin.

ex.
points = [
    [1, 1],
    [3, 3],
    [2, 2],
    [4, 4],
    [-1, -1]
], k = 3
-> [[-1, -1], [1, 1], [2, 2]]
*/

void printPair(pair<int, int> p) {
    cout << "(" << p.first << ", " << p.second << ")";
}

void print(vector<pair<int, int> > arr) {
    if (arr.size() == 0) {
        cout << "[]\n";
        return;
    }
    cout << "[";
    for (int i = 0; i < arr.size() - 1; i++) {
        printPair(arr[i]);
        cout << ", ";
    }
    printPair(arr.back());
    cout << "]\n";
}

int distToOrigin(pair<int, int> p) {
    return p.first * p.first + p.second * p.second;
}

struct Comparator {
    bool operator() (const pair<int, int>& p1, const pair<int, int>& p2) const {
        return distToOrigin(p1) < distToOrigin(p2);
    }
};

/* APPROACH 1: min heap, with priority by distance to origin. O(N log K) */
vector<pair<int, int> > kClosestPoints(vector<pair<int, int> > points, int k) {
    priority_queue<pair<int, int>, vector<pair<int, int> >, Comparator > minHeap;
    for (int i = 0; i < k; i++) {
        minHeap.push(points[i]);
    }
    for (int i = k; i < points.size(); i++) {
        if (distToOrigin(points[i]) < distToOrigin(minHeap.top())) {
            minHeap.pop();
            minHeap.push(points[i]);
        }
    }
    vector<pair<int, int> > ans;
    while (!minHeap.empty()) {
        ans.push_back(minHeap.top());
        minHeap.pop();
    }
    return ans;
}

/* APPROACH 2: same as approach 1, but cleaner min-heap implementation. */
vector<pair<int, int> > kClosestPoints2(vector<pair<int, int> > points, int k) {
    priority_queue<pair<int, pair<int, int> > > minHeap;
    for (int i = 0; i < points.size(); i++) {
        minHeap.push(make_pair(distToOrigin(points[i]), points[i]));
        if (minHeap.size() > k) minHeap.pop();
    }
    vector<pair<int, int> > ans;
    while (!minHeap.empty()) {
        ans.push_back(minHeap.top().second);
        minHeap.pop();
    }
    return ans;
}

/* APPROACH 3: quickSelect (D&Q), pretty much partial quickSort. O(N) avg, O(N^2) worst case. */
int partialSort(vector<pair<int, int> > &points, int l, int r) {
    pair<int, int> splitter = points[r];
    int m = l;
    for (int i = l; i < r; i++) {
        if (distToOrigin(points[i]) < distToOrigin(splitter)) {
            pair<int, int> temp = points[i];
            points[i] = points[m];
            points[m] = temp;
            m++;
        }
    }
    points[r] = points[m];
    points[m] = splitter;
    return m;
}
vector<pair<int, int> > kClosestPoints3(vector<pair<int, int> > &points, int k) {
    int origK = k;
    int l = 0, r = points.size() - 1;
    int m = 0;
    while (true) {
        m = partialSort(points, l, r);
        int leftLength = m - l + 1;
        if (k < leftLength) {
            r = m - 1;
        } else if (k > leftLength) {
            l = m + 1;
            k -= leftLength;
        } else break;
    }
    vector<pair<int, int> > ans;
    for (int i = 0; i < origK; i++) {
        ans.push_back(points[i]);
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<pair<int, int> > points = {
        {1, 1},
        {3, 3},
        {2, 2},
        {4, 4},
        {-1, -1}
    };
    int k = 3;

    cout << "APPROACH 1 TESTING: ";
    print(kClosestPoints(points, k));
    cout << "APPROACH 2 TESTING: ";
    print(kClosestPoints2(points, k));
    cout << "APPROACH 3 TESTING: ";
    print(kClosestPoints3(points, k));
    return 0;
}
