#include <iostream>
#include <queue>
#include <unordered_set>
using namespace std;

/*
You are only allowed to perform 2 operations, multiply a number by 2, or subtract a number by 1. Given
a number x and a number y, find the minimum number of operations needed to go from x to y.

ex. x = 6, y = 20 -> 3
(((6 - 1) * 2) * 2) = 20
*/

/*
QUESTION: x, y > 0 ? Will assume yes for simplicity
*/

struct Node {
    int val;
    int operations;
};

/* APPROACH 1: BFS. Track number of operations and current value in each BFS node, and also track
visited values. */
int minOperations(int x, int y) {
    queue<Node> q;
    unordered_set<int> visited;
    Node n = {x, 0};
    q.push(n);
    while (!q.empty()) {
        Node t = q.front();
        q.pop();
        if (t.val == y) return t.operations;
        visited.insert(t.val);
        if (t.val * 2 == y || t.val - 1 == y) {
            return t.operations + 1;
        }
        if (visited.find(t.val * 2) == visited.end()) {
            Node next = {t.val * 2, t.operations + 1};
            q.push(next);
        }
        if (t.val >= 0 && visited.find(t.val - 1) == visited.end()) {
            Node next = {t.val - 1, t.operations + 1};
            q.push(next);
        }
    }
    return -1;
}

int main(int main, char **argc) {
    int x = 6, y = 21;
    cout << minOperations(x, y) << '\n';
    return 0;
}
