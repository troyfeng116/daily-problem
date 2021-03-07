#include <iostream>
#include <vector>
using namespace std;

/*
Given a sorted array, convert it into a binary search tree.
*/

/* QUESTION: must be balanced? Will assume yes (or trivial) */

typedef struct TreeNode *Node;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int v) {
        val = v;
        left = nullptr;
        right = nullptr;
    }
    TreeNode(int v, TreeNode *l, TreeNode *r) {
        val = v;
        left = l;
        right = r;
    }
    void print() {
        if (left != nullptr) left->print();
        cout << val << " ";
        if (right != nullptr) right->print();
    }
};

/* APPROACH 1: Recursion. O(N) */
Node aux(vector<int> arr, int l, int r) {
    if (l > r) return nullptr;
    if (l == r) return new TreeNode(arr[l]);
    int m = (l + r) / 2;
    Node node = new TreeNode(arr[m], aux(arr, l, m - 1), aux(arr, m + 1, r));
    return node;
}
Node arrToBST(vector<int> arr) {
    return aux(arr, 0, arr.size() - 1);
}

int main(int argc, char **argv) {
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9};

    arrToBST(arr)->print();
    cout << '\n';
    return 0;
}
