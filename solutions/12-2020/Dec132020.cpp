#include <iostream>
using namespace std;

/*
Given a binary tree and an integer k, filter the binary tree such that its leaves don't contain the value k.
Here are the rules:

- If a leaf node has a value of k, remove it.
- If a parent node has a value of k, and all of its children are removed, remove it.
*/

typedef struct TreeNode *Node;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int v) {
        val = v;
        left = NULL;
        right = NULL;
    }
    TreeNode(int v, TreeNode *l, TreeNode *r) {
        val = v;
        left = l;
        right = r;
    }
};
void printInorder(Node root) {
    if (root == NULL) return;
    if (root->left != NULL) printInorder(root->left);
    std::cout << root->val << " ";
    if (root->right != NULL) printInorder(root->right);
}

/* APPROACH 1: Postorder recursion. Keep track of parent in recursive calls, modifies original tree. O(N) */
void dfs(Node cur, int k, Node parent, bool left) {
    if (cur == NULL) return;
    dfs(cur->left, k, cur, true);
    dfs(cur->right, k, cur, false);
    if (cur->left == NULL && cur->right == NULL && cur->val == k) {
        if (left) parent->left = NULL;
        else parent->right = NULL;
    }
}
Node filterLeaves(Node root, int k) {
    Node dummy = new TreeNode(0);
    dummy->left = root;
    dfs(root, k, dummy, true);
    return dummy->left;
}

/* APPROACH 2: Also postorder, preserving original tree. O(N) */
Node filterLeaves2(Node root, int k) {
    if (root == NULL) return nullptr;
    root->left = filterLeaves2(root->left, k);
    root->right = filterLeaves2(root->right, k);
    if (root->left == NULL && root->right == NULL && root->val == k) {
        return nullptr;
    }
    return root;
}

int main(int argc, char **argv) {
    Node root1 = new TreeNode(1,
        new TreeNode(1, new TreeNode(2), NULL),
        new TreeNode(1, new TreeNode(1), NULL));
    int k = 1;
    Node res1 = filterLeaves(root1, k);
    std::cout << "APPROACH 1 TESTING: ";
    printInorder(res1);
    std::cout << '\n';

    Node root2 = new TreeNode(1,
        new TreeNode(1, new TreeNode(2), NULL),
        new TreeNode(1, new TreeNode(1), NULL));
    Node res2 = filterLeaves2(root2, k);
    std::cout << "APPROACH 2 TESTING: ";
    printInorder(res2);
    std::cout << '\n';

    return 0;
}
