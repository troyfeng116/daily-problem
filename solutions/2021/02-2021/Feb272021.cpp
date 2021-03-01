#include <iostream>
using namespace std;

/*
Given two binary trees that are duplicates of one another, and given a node in one tree, find
that corresponding node in the second tree.

For this problem, you can assume that there can be duplicate values in the tree (so
comparing node1.value == node2.value isn't going to work).

#  1
# / \
#2   3
#   / \
#  4*  5
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

/* APPROACH 1: dfs recursion. O(N) */
Node dfs(Node cur, Node target, Node cloneCur) {
    if (cur == nullptr) return nullptr;
    if (cur == target) return cloneCur;
    Node left = dfs(cur->left, target, cloneCur->left);
    if (left != nullptr) return left;
    return dfs(cur->right, target, cloneCur->right);
}
Node searchForNodeInClone(Node root, Node target, Node cloneRoot) {
    return dfs(root, target, cloneRoot);
}

int main(int argc, char **argv) {
    Node tree = new TreeNode(1,
        new TreeNode(2),
        new TreeNode(3, new TreeNode(4), new TreeNode(5)));
    Node target = tree->right->left;
    Node clone = new TreeNode(1,
        new TreeNode(2),
        new TreeNode(3, new TreeNode(4), new TreeNode(5)));

    cout << searchForNodeInClone(tree, target, clone)->val << '\n';
    return 0;
}
