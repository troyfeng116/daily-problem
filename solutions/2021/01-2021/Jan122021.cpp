#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
Given a list of points as a tuple (x, y) and an integer k, find the k closest points to the origin (0, 0).
*/

void printPoint(pair<int, int> point) {
    std::cout << "(" << point.first << ", " << point.second << ")";
}
void print(vector<pair<int, int> > points) {
    std::cout << "[";
    for (int i = 0; i < points.size() - 1; i++) {
        printPoint(points[i]);
        std::cout << ", ";
    }
    printPoint(points[points.size() - 1]);
    std::cout << "]\n";
}
int myCompare(pair<int, int> p1, pair<int, int> p2) {
    return p1.first * p1.first + p1.second * p1.second - (p2.first * p2.first + p2.second * p2.second);
}

/* APPROACH 1: Sort list of points by distance to (0, 0) and return first k. O(N log N) time, O(N) space */
void sort(vector<pair<int, int> > &points, int l, int r) {
    if (l < r) {
        pair<int, int> splitter = points[r];
        int m = l;
        for (int i = l; i < r; i++) {
            if (myCompare(points[i], splitter) < 0) {
                pair<int, int> temp = points[i];
                points[i] = points[m];
                points[m] = temp;
                m++;
            }
        }
        points[r] = points[m];
        points[m] = splitter;
        sort(points, l, m-1);
        sort(points, m+1, r);
    }
}
vector<pair<int, int> > kClosest(vector<pair<int, int> > points, int k) {
    sort(points, 0, points.size() - 1);
    vector<pair<int, int> > ans;
    for (int i = 0; i < min(k, (int) points.size()); i++) {
        ans.push_back(points[i]);
    }
    return ans;
}

/* APPROACH 2: max heap. Keep k points closest to origin in a max heap and keep popping the farthest away if there is a closer point.
O(N log K) time, O(K) space */
typedef pair<int, int> myPair;
vector<pair<int, int> > kClosest2(vector<pair<int, int> > points, int k) {
    auto cmp = [](myPair p1, myPair p2) {
        return p1.first * p1.first + p1.second * p1.second < p2.first * p2.first + p2.second * p2.second;
    };
    priority_queue<myPair, vector<myPair>, decltype(cmp)> maxHeap(cmp);
    for (int i = 0; i < min(k, (int) points.size()); i++) {
        maxHeap.push(points[i]);
    }
    for (int i = k; i < points.size(); i++) {
        if (myCompare(points[i], maxHeap.top()) < 0) {
            maxHeap.pop();
            maxHeap.push(points[i]);
        }
    }
    vector<pair<int, int> > ans;
    while (!maxHeap.empty()) {
        ans.push_back(maxHeap.top());
        maxHeap.pop();
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<pair<int, int> > points = {{13, 0}, {0, 0}, {1, 2}, {-3, 4}, {3, 1}};
    
    std::cout << "APPROACH 1 TESTING: ";
    vector<pair<int, int> > res1 = kClosest(points, 2);
    print(res1);

    std::cout << "APPROACH 2 TESTING: ";
    vector<pair<int, int> > res2 = kClosest2(points, 2);
    print(res2);
    return 0;
}
