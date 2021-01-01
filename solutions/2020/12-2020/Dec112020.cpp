#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
Given a list of points, an integer k, and a point p, find the k closest points to p.
*/

struct Point {
    int x;
    int y;
    Point() {
        x = 0;
        y = 0;
    }
    Point(int a, int b) {
        x = a;
        y = b;
    }
};

void printPoint(Point *p) {
    std::cout << "(" << p->x << ", " << p->y << ")";
}

// Since sqrt is monotone increasing, no need to take sqrt for purpose of comparison
int distance(Point *p1, Point *p2) {
    int dx = p1->x - p2->x;
    int dy = p1->y - p2->y;
    return dx*dx + dy*dy;
}

void print(vector<Point *> arr) {
    std::cout << "[";
    for (int i = 0; i < arr.size() - 1; i++) {
        printPoint(arr[i]);
        std::cout << ", ";
    }
    printPoint(arr[arr.size()-1]);
    std::cout << "]\n";
}

/* APPROACH 1: Sort and take first k. O(N log N) */
void sort(vector<Point *> &arr, int l, int r, Point *p) {
    if (l < r) {
        Point *splitter = arr[r];
        int dist = distance(splitter, p);
        int m = l;
        for (int i = l; i < r; i++) {
            if (distance(arr[i], p) < dist) {
                Point *temp = arr[i];
                arr[i] = arr[m];
                arr[m] = temp;
                m++;
            }
        }
        arr[r] = arr[m];
        arr[m] = splitter;
        sort(arr, l, m-1, p);
        sort(arr, m+1, r, p);
    }
}
vector<Point *> kClosestPoints(vector<Point *> &arr, Point *p, int k) {
    sort(arr, 0, arr.size() - 1, p);
    vector<Point *> ans;
    for (int i = 0; i < min(k, (int) arr.size()); i++) {
        ans.push_back(arr[i]);
    }
    return ans;
}

/* APPROACH 2: Heap. Priority assigned based on distance to p. O(N log k) */
vector<Point *> kClosestPoints2(vector<Point *> &arr, Point *p, int k) {
    auto cmp = [&](Point *a, Point *b) { return distance(a, p) < distance(b, p); };
    priority_queue<Point *, vector<Point *>, decltype(cmp)> heap(cmp);
    for (int i = 0; i < min(k, (int) arr.size()); i++) {
        heap.push(arr[i]);
    }
    for (int i = min(k, (int) arr.size()); i < arr.size(); i++) {
        heap.pop();
        heap.push(arr[i]);
    }
    vector<Point *> ans;
    while (!heap.empty()) {
        ans.push_back(heap.top());
        heap.pop();
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<Point *> arr = {
        new Point(0, 0),
        new Point(1, 1),
        new Point(2, 2),
        new Point(3, 3)
    };
    Point *p = new Point(0, 3);
    int k = 3;

    std::cout << "APPROACH 1 TESTING: ";
    vector<Point *> res1 = kClosestPoints(arr, p, k);
    print(res1);

    vector<Point *> arr2 = {
        new Point(0, 0),
        new Point(1, 1),
        new Point(2, 2),
        new Point(3, 3)
    };
    std::cout << "APPROACH 2 TESTING: ";
    vector<Point *> res2 = kClosestPoints2(arr2, p, k);
    print(res2);

    return 0;
}
