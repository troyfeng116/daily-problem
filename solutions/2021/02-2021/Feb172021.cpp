#include <iostream>
using namespace std;

/*
A number can be constructed by a path from the root to a leaf. Given a binary tree, sum all
the numbers that can be constructed from the root to all leaves.

ex.
      1
    /   \
   2     3
  / \
 4   5
-> 124 + 125 + 13 = 262
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

/* APPROACH 1: Recursion. O(N) */
int aux(Node root, int num) {
    if (root == nullptr) return 0;
    if (root->left == nullptr && root->right == nullptr) {
        return num * 10 + root->val;
    }
    return aux(root->left, num * 10 + root->val) + aux(root->right, num * 10 + root->val);
}
int sumAllRootToLeafPaths(Node root) {
    return aux(root, 0);
}

int main(int argc, char **argv) {
    Node tree = new TreeNode(1,
        new TreeNode(2, new TreeNode(4), new TreeNode(5)),
        new TreeNode(3));
    cout << sumAllRootToLeafPaths(tree) << '\n';
    return 0;
}
