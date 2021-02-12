#include <iostream>
using namespace std;

/*
Given a binary tree, and a target number, find if there is a path from the root to any leaf that sums up to the target.

      1
    /   \
   2     3
    \     \
     6     4
target = 9 -> true (1 + 2 + 6)
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

/* APPROACH 1: Simple backtracking. O(N) */
bool hasPathSum(Node node, int target) {
    if (node == nullptr) return false;
    if (node->left == nullptr && node->right == nullptr && node->val == target) return true;
    return hasPathSum(node->left, target - node->val) || hasPathSum(node->right, target - node->val);
}

int main(int argc, char **argv) {
    Node tree = new TreeNode(1,
        new TreeNode(2, nullptr, new TreeNode(6)),
        new TreeNode(3, nullptr, new TreeNode(4)));
    int target = 9;
    cout << hasPathSum(tree, target) << '\n';
    return 0;
}
