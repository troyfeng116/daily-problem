#include <iostream>
using namespace std;

/*
You are given the root of a binary tree. Return the deepest node (the furthest node from the root).

Example:

    a
   / \
  b   c
 /
d

The deepest node in this tree is d at depth 3.
*/

/* QUESTION: is deepest node unique? If not, which to return, any or leftmost? Will assume we
can return any of the deepest nodes. */

typedef struct TreeNode *Node;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
};
void inorder(Node tree) {
    if (tree == NULL) return;
    if (tree->left != NULL) inorder(tree->left);
    std::cout << tree->val << " ";
    if (tree->right != NULL) inorder(tree->right);
}
Node createNode(int val) {
    Node newNode = new TreeNode;
    newNode->val = val;
    newNode->left = NULL;
    newNode->right = NULL;
    return newNode;
}

/* APPROACH 1: Recursion, pass depth up using pointers. */
int deepestNodeAux(Node root, int *dist) {
    std::cout << root->val << " at level " << *dist << '\n';
    if (root->left == NULL && root->right == NULL) {
        return root->val;
    }
    int thisHeight = *dist;
    int maxDist = thisHeight;
    int ans = 0;
    if (root->left != NULL) {
        (*dist)++;
        int n1 = deepestNodeAux(root->left, dist);
        if (*dist > maxDist) {
            maxDist = *dist;
            ans = n1;
        }
    }
    if (root->right != NULL) {
        (*dist) = thisHeight;
        (*dist)++;
        int n1 = deepestNodeAux(root->right, dist);
        if (*dist > maxDist) {
            maxDist = *dist;
            ans = n1;
        }
    }
    return ans;
}
int deepestNode(Node root) {
    int height = 0;
    return deepestNodeAux(root, &height);
}

int main(int argc, char **argv) {
    Node root = createNode(1);
    Node n2 = createNode(2);
    Node n3 = createNode(3);
    Node n4 = createNode(4);
    Node n5 = createNode(5);
    Node n6 = createNode(6);
    Node n7 = createNode(7);
    Node n8 = createNode(8);
    Node n9 = createNode(9);
    root->left = n2;
    n2->left = n4;
    n2->right = n5;
    n4->right = n6;
    n6->left = n7;
    root->right = n3;
    n3->left = n8;
    n3->right = n9;
    inorder(root);
    std::cout << '\n';
    std::cout << deepestNode(root) << '\n';
    return 0;
}
