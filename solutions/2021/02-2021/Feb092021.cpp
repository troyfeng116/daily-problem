#include <iostream>
#include <queue>
using namespace std;

/*
Given a binary tree, find the minimum depth of the binary tree. The minimum depth is the shortest distance
from the root to a leaf.

ex.
     1
    / \
   2   3
        \
         4
-> 2
*/

typedef struct TreeNode *Node;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int v) {
        val = v;
        left = nullptr, right = nullptr;
    }
    TreeNode(int v, TreeNode *l, TreeNode *r) {
        val = v;
        left = l;
        right = r;
    }
};

/* APPROACH 1: recursion. O(N) */
int minDepth(Node tree) {
    if (tree == nullptr) return 0;
    int l = minDepth(tree->left);
    int r = minDepth(tree->right);
    if (l == 0) return r + 1;
    if (r == 0) return l + 1;
    return min(l, r) + 1;
}

/* APPROACH 2: BFS. O(N) */
int minDepth2(Node tree) {
    if (tree == nullptr) return 0;
    int depth = 1;
    queue<Node> q;
    q.push(tree);
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            Node t = q.front();
            q.pop();
            if (t->left == nullptr && t->right == nullptr) return depth;
            if (t->left != nullptr) q.push(t->left);
            if (t->right != nullptr) q.push(t->right);
        }
        depth++;
    }
    return depth;
}

int main(int argc, char **argv) {
    Node test = new TreeNode(1, new TreeNode(2), new TreeNode(3, nullptr, new TreeNode(4)));
    cout << "APPROACH 1 TESTING: " << minDepth(test) << '\n';
    cout << "APPROACH 2 TESTING: " << minDepth2(test) << '\n';
    return 0;
}
