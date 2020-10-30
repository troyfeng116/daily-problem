#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

/*
You are given the root of a binary tree, along with two nodes, A and B. Find and return the lowest common 
ancestor of A and B. For this problem, you can assume that each node also has a pointer to its parent, 
along with its left and right child.

ex.
   1
  / \
 2   3
    / \
   4*  5*
Lowest common ancestor of nodes 4 and 5 is node 3.
*/

typedef struct TreeNode *Node;
struct TreeNode {
    int val;
    TreeNode *left, *right, *parent;
    TreeNode(int v) {
        val = v;
        left = NULL, right = NULL, parent = NULL;
    }
    TreeNode(int v, TreeNode *l, TreeNode *r) {
        val = v, left = l, right = r;
        l->parent = this;
        r->parent = this;
    }
};

/* APPROACH 1: Store all ancestors of A in set, then compare ancestors of B until found. O(H) */
Node lowestCommonAncestor(Node root, Node A, Node B) {
    unordered_set<Node> table;
    while (A != NULL) {
        table.insert(A);
        A = A->parent;
    }
    while (B != NULL) {
        if (table.count(B) > 0) return B;
        B = B->parent;
    }
    return NULL;
}

/* APPROACH 2: If no parent pointer, we would dfs to return path from root to A and B, then compare the
paths and return first point where equal. */

int main(int argc, char **argv) {
    Node root = new TreeNode(1,
        new TreeNode(2),
        new TreeNode(3));
    Node A = new TreeNode(4);
    root->right->left = A;
    A->parent = root->right;
    Node B = new TreeNode(5);
    root->right->right = B;
    B->parent = root->right;

    Node res = lowestCommonAncestor(root, A, B);
    std::cout << (res != NULL ? res->val : 0) << '\n';
    return 0;
}
