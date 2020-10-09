#include <iostream>
using namespace std;

/*
Given a binary tree, remove the nodes in which there is only 1 child, so that the binary tree is a full binary tree.

So leaf nodes with no children should be kept, and nodes with 2 children should be kept as well.
*/

typedef struct TreeNode *Node;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int v) {
        val = v;
        left = NULL, right = NULL;
    }
    TreeNode (int v, TreeNode *l, TreeNode *r) {
        val = v;
        left = l;
        right = r;
    }
};
void printInOrder(Node tree) {
    if (tree == NULL) return;
    printInOrder(tree->left);
    std::cout << tree->val << " ";
    printInOrder(tree->right);
}

/* APPROACH 1: Recursion, preorder. Runs in O(N) */
Node removeNonFullNodes(Node root) {
    if (root == NULL) return NULL;
    root->left = removeNonFullNodes(root->left);
    root->right = removeNonFullNodes(root->right);
    if (root->left == NULL && root->right == NULL) return root;
    if (root->left == NULL) {
        Node newRoot = root->right;
        delete root;
        return newRoot;
    }
    if (root->right == NULL) {
        Node newRoot = root->left;
        delete root;
        return newRoot;
    }
    return root;
}

int main(int argc, char **argv) {
    Node tree = new TreeNode(1,
        new TreeNode(2, new TreeNode(0), NULL),
        new TreeNode(3, new TreeNode(9), new TreeNode(4)));
    printInOrder(tree);
    std::cout << '\n';
    removeNonFullNodes(tree);
    printInOrder(tree);
    std::cout << '\n';
    return 0;
}
