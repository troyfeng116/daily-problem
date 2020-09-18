#include <iostream>
using namespace std;

/*
Hi, here's your problem today. This problem was recently asked by Microsoft:

You are given the preorder and inorder traversals of a binary tree in the form of arrays. Write 
a function that reconstructs the tree represented by these traversals.

Example:
Preorder: [a, b, d, e, c, f, g]
Inorder: [d, b, e, a, f, c, g]

The tree that should be constructed from these traversals is:

    a
   / \
  b   c
 / \ / \
d  e f  g
*/

/* 
QUESTIONS: Need to validate that preorder and inorder can actually make a binary tree? Will
assume no
*/

typedef struct TreeNode *Node;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
};
Node createNode(int val) {
    Node ans = new TreeNode;
    ans->val = val;
    ans->left = NULL;
    ans->right = NULL;
    return ans;
}
void printInOrder(Node root) {
    if (root == NULL) ;
    else {
        printInOrder(root->left);
        std::cout << root->val << ' ';
        printInOrder(root->right);
    }
}
void printPreOrder(Node root) {
    if (root == NULL) ;
    else {
        std::cout << root->val << ' ';
        printPreOrder(root->left);
        printPreOrder(root->right);
    }
}

/* APPROACH 1: Traverse preorder to make recursive call. Search in inorder: anything
to the left is left subtree, and anything to right is right subtree. Once we pick a
root from preorder, that root is at index m in inorder. This blocks off l to m-1 for
the left subtree and m+1 to r for the right subtree. preIndex makes one pass, so there
are N recursive calls for O(N). */
int search(int arr[], int l, int r, int target) {
    for (int i = l; i <= r; i++) {
        if (arr[i] == target) return i;
    }
    return -1;
}
Node constructTreeAux(int preorder[], int inorder[], int inStart, int inEnd) {
    static int preIndex = 0;
    if (inStart > inEnd) return NULL;
    Node root = createNode(preorder[preIndex]);
    preIndex++;
    int inIndex = search(inorder, inStart, inEnd, root->val);
    root->left = constructTreeAux(preorder, inorder, inStart, inIndex-1);
    root->right = constructTreeAux(preorder, inorder, inIndex+1, inEnd);
    return root;
}
Node constructTree(int preorder[], int inorder[], int n) {
    return constructTreeAux(preorder, inorder, 0, n-1);
}

int main(int argc, char **argv) {
    int n = 7;
    int preorder[] = {1, 2, 4, 5, 3, 6, 7};
    int inorder[] = {4, 2, 5, 1, 6, 3, 7};
    Node result = constructTree(preorder, inorder, n);
    printPreOrder(result);
    std::cout << '\n';
    printInOrder(result);
    std::cout << '\n';
    return 0;
}
