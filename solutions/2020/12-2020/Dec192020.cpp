#include <iostream>
#include <vector>
using namespace std;

/*
Given a node in a binary search tree (may not be the root), find the next largest node in 
the binary search tree (also known as an inorder successor). The nodes in this binary search 
tree will also have a parent field to traverse up the tree.

ex. 
     3
    / \
   2   4
  /     \
 1       5

inorderSuccessor(Node(3)) => Node(4), inorderSuccessor(Node(2)) => Node(3)
*/

typedef struct TreeNode *Node;
struct TreeNode {
    int val;
    TreeNode *left, *right, *parent;
    TreeNode(int v) {
        val = v;
        left = NULL, right = NULL, parent = NULL;
    }
    TreeNode(int v, TreeNode *p) {
        val = v;
        left = NULL, right = NULL, parent = p;
    }
    TreeNode(int v, TreeNode *l, TreeNode *r, TreeNode *p) {
        val = v;
        left = l, right = r, parent = p;
    }
};
void insert(Node *root, int val) {
    if (*root == NULL) *root = new TreeNode(val);
    else {
        if (val < (*root)->val) {
            if ((*root)->left == NULL) (*root)->left = new TreeNode(val, *root);
            else insert(&(*root)->left, val);
        }
        else {
            if ((*root)->right == NULL) (*root)->right = new TreeNode(val, *root);
            else insert(&(*root)->right, val);
        }
    }
}

/* APPROACH 1: find and store inorder traversal, search for node, and return next node.
O(N) space + time */
void dfs(Node node, vector<Node> &ans) {
    if (node != NULL) {
        dfs(node->left, ans);
        ans.push_back(node);
        dfs(node->right, ans);
    }
}
Node inorderSuccessor(Node node) {
    if (node == NULL) {
        std::cout << "Root is NULL\n";
        return new TreeNode(-1);
    }
    Node root = node;
    while (root->parent != NULL) root = root->parent;
    vector<Node> inorder;
    dfs(root, inorder);
    for (int i = 0; i < inorder.size() - 1; i++) {
        if (inorder[i]->val == node->val) return inorder[i+1];
    }
    std::cout << "Node with value " << node->val << " is largest node in BST\n";
    return new TreeNode(-1);
}

/* APPROACH 2: If node has a right child, return leftmost child of that right child.
Else, return first ancestor that is greater than child. O(h) */
Node inorderSuccessor2(Node node) {
    if (node == NULL) {
        std::cout << "Root is NULL\n";
        return new TreeNode(-1);
    }
    Node cur = node;
    if (cur->right != NULL) {
        cur = cur->right;
        while (cur->left != NULL) cur = cur->left;
        return cur;
    }
    // Traverse parents until ancestor > node is found.
    while (cur != NULL && cur->val <= node->val) cur = cur->parent;
    if (cur == NULL) {
        std::cout << "Node with value " << node->val << " is largest node in BST\n";
        return new TreeNode(-1);
    }
    return cur;
}

int main(int argc, char **argv) {
    Node root = new TreeNode(3);
    insert(&root, 2);
    insert(&root, 4);
    insert(&root, 1);
    insert(&root, 5);

    std::cout << "APPROACH 1 TESTING: \n";
    std::cout << inorderSuccessor(root->left)->val << '\n';
    std::cout << inorderSuccessor(root->right)->val << '\n';

    std::cout << "APPROACH 2 TESTING: \n";
    std::cout << inorderSuccessor2(root->left)->val << '\n';
    std::cout << inorderSuccessor2(root->right)->val << '\n';
    return 0;
}
