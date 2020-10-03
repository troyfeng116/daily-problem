#include <iostream>
using namespace std;

/*
You are given a binary tree representation of an arithmetic expression. In this tree, each 
leaf is an integer value, and a non-leaf node is one of the four operations: '+', '-', 
'*', or '/'.

Write a function that takes this tree and evaluates the expression.

Example:

    *
   / \
  +    +
 / \  / \
3  2  4  5

This is a representation of the expression (3 + 2) * (4 + 5), and should return 45.
*/

/* QUESTION: Assume valid? i.e. all non-leaf nodes (operators) have 2 children */

typedef struct TreeNode *Node;
struct TreeNode {
    char val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(char v) {
        val = v;
        left = NULL, right = NULL;
    }
    TreeNode(char v, Node l, Node r) {
        val = v;
        left = l, right = r;
    }
};

/* APPROACH 1: Recursion. O(N) time */
int eval(Node tree) {
    if (tree == NULL) return 0;
    if (tree->left == NULL && tree->right == NULL) return tree->val-'0';
    switch (tree->val) {
        case '+':
            return eval(tree->left) + eval(tree->right);
        case '-':
            return eval(tree->left) - eval(tree->right);
        case '*':
            return eval(tree->left) * eval(tree->right);
        case '/':
            return eval(tree->left) / eval(tree->right);
        default:
            std::cout << "INVALID TREE\n";
            return 0;
    }
}

int main(int argc, char **argv) {
    Node root = new TreeNode('*', 
        new TreeNode('+', new TreeNode('3'), new TreeNode('2')),
        new TreeNode('-', new TreeNode('4'), new TreeNode('5')));
    std::cout << eval(root) << '\n';
    return 0;
}
