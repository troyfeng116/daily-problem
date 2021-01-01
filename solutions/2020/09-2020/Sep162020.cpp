#include <iostream>
using namespace std;

/*
A unival tree is a tree where all the nodes have the same value. Given a binary tree, return the 
number of unival subtrees in the tree.

For example, the following tree should return 5:

   0
  / \
 1   0
    / \
   1   0
  / \
 1   1

The 5 trees ar e:
- The three single '1' leaf nodes. (+3)
- The single '0' leaf node. (+1)
- The [1, 1, 1] tree at the bottom. (+1)
*/

typedef struct TreeNode *Node;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
};
Node createTree(int v) {
    Node ans = new TreeNode;
    ans->val = v;
    ans->left = NULL;
    ans->right = NULL;
    return ans;
}

/* APPROACH 1: Simple top-down recursion. Runs in O(N^2) time: we're double checking all
children of each node. */
bool isUnivalTree(Node root) {
    if (root == NULL) return true;
    if (root->left == NULL && root->right == NULL) return true;
    if (root->left == NULL) return isUnivalTree(root->right) && root->val==root->right->val;
    if (root->right == NULL) return isUnivalTree(root->left) && root->val==root->left->val;
    return isUnivalTree(root->left) && isUnivalTree(root->right) 
        && root->left->val==root->val && root->val==root->right->val;
}
int numUnivalTrees(Node root) {
    if (root->left == NULL || root->right == NULL) return 1;
    if (root->left == NULL) {
        int right = numUnivalTrees(root->right);
        return isUnivalTree(root) ? right+1 : right;
    }
    if (root->right == NULL) {
        int left = numUnivalTrees(root->left);
        return isUnivalTree(root) ? left+1 : left;
    }
    int left = numUnivalTrees(root->left);
    int right = numUnivalTrees(root->right);
    return isUnivalTree(root) ? left+right+1 : left+right;
}

/* APPROACH 2: Get rid of extra child checks by passing count up through recursive calls as
a pointer parameter. O(N) */
bool countUnivalTrees(Node root, int &count) {
    if (root == NULL) return true;
    bool left = countUnivalTrees(root->left, count);
    bool right = countUnivalTrees(root->right, count);
    if (!left || !right) return false;
    if (root->left != NULL && root->val != root->left->val) return false;
    if (root->right != NULL && root->val != root->right->val) return false;
    count++;
    return true;
}
int numUnivalTrees2(Node root) {
    int count = 0;
    countUnivalTrees(root, count);
    return count;
}

int main(int argc, char **argv) {
    Node root = createTree(0);
    Node n1 = createTree(1);
    Node n2 = createTree(0);
    Node n3 = createTree(1);
    Node n4 = createTree(1);
    Node n5 = createTree(1);
    Node n6 = createTree(0);
    root->left = n1;
    root->right = n2;
    root->right->left = n3;
    root->right->left->left = n4;
    root->right->left->right = n5;
    root->right->right = n6;
    std::cout << numUnivalTrees(root) << '\n';
    std::cout << numUnivalTrees2(root) << '\n';
    return 0;
}
