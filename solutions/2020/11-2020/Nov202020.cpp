#include <iostream>
#include <vector>
using namespace std;

/*
Given a sorted list, create a height balanced binary search tree, meaning the height differences of 
each node can only differ by at most 1.
*/

/* APPROACH 1: implement AVL tree insertion. O(N log N) */
typedef struct TreeNode *Node;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    int height;
    TreeNode(int v) {
        val = v;
        left = NULL, right = NULL;
        // All new nodes are inserted at leaf.
        height = 1;
    }
};
void printPreorder(Node root) {
    if (root == NULL) return;
    std::cout << root->val << ' ';
    printPreorder(root->left);
    printPreorder(root->right);
}
int height(Node n) {
    return n == NULL ? 0 : n->height;
}
int getBalance(Node root) {
    if (root == NULL) return 0;
    return height(root->left) - height(root->right);
}
// Rotate right (correct left imbalance at root)
Node rightRotate(Node root) {
    Node lChild = root->left;
    Node lrGChild = root->left->right;
    lChild->right = root;
    root->left = lrGChild;
    root->height = max(height(root->left), height(root->right)) + 1;
    lChild->height = max(height(lChild->left), height(lChild->right)) + 1;
    return lChild;
}
// Rotate left
Node leftRotate(Node root) {
    Node rChild = root->right;
    Node rlGChild = root->right->left;
    rChild->left = root;
    root->right = rlGChild;
    root->height = max(height(root->left), height(root->right)) + 1;
    rChild->height = max(height(rChild->left), height(rChild->right)) + 1;
    return rChild;
}
Node insert(Node root, int v) {
    if (root == NULL) return new TreeNode(v);
    if (v < root->val) root->left = insert(root->left, v);
    if (v > root->val) root->right = insert(root->right, v);
    root->height = 1 + max(height(root->left), height(root->right));
    int balance = getBalance(root);
    if (balance > 1) {
        // Left left
        if (v < root->left->val) return rightRotate(root);
        // Left right
        else {
            root->left = leftRotate(root->left);
            return rightRotate(root);
        }
    }
    else if (balance < -1) {
        // Right right
        if (v > root->right->val) return leftRotate(root);
        // Right left
        else {
            root->right = rightRotate(root->right);
            return leftRotate(root);
        }
    }
    return root;
}
Node arrToTree(vector<int> arr) {
    Node root = NULL;
    for (int i = 0; i < arr.size(); i++) {
        root = insert(root, arr[i]);
    }
    return root;
}

/* APPROACH 2: Recursion. Add middle of [l,r] as root and recurse. O(N) */
Node aux(vector<int> arr, int l, int r) {
    if (l > r) return NULL;
    int m = (l+r)/2;
    Node root = new TreeNode(arr[m]);
    root->left = aux(arr, l, m-1);
    root->right = aux(arr, m+1, r);
    return root;
}
Node arrToTree2(vector<int> arr) {
    return aux(arr, 0, arr.size()-1);
}

int main(int argc, char **argv) {
    vector<int> arr = {1, 2, 3, 4, 5, 6, 7, 8};
    Node res = arrToTree(arr);
    std::cout << "APPROACH 1 TESTING: ";
    printPreorder(res);
    std::cout << '\n';

    Node res2 = arrToTree2(arr);
    std::cout << "APPROACH 2 TESTING: ";
    printPreorder(res2);
    std::cout << '\n';
    return 0;
}
