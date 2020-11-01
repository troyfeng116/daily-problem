#include <iostream>
#include <vector>
using namespace std;

/*
Given a sorted list of numbers, change it into a balanced binary search tree. You can assume there will 
be no duplicate numbers in the list.
*/

/* BST definition */
typedef struct Node *BSTNode;
struct Node {
    int val;
    Node *left;
    Node *right;
};
bool aux(BSTNode root, int min, int max) {
    if (root == NULL) return true;
    if (root->val <= min || root->val >= max) return false;
    return aux(root->left, min, root->val) && aux(root->right, root->val, max);
}
bool assertBST(BSTNode root) {
    return aux(root, INT_MIN, INT_MAX);
}
void printInorder(BSTNode root) {
    if (root == NULL) ;
    else {
        printInorder(root->left);
        std::cout << root->val << " ";
        printInorder(root->right);
    }
}

/* APPROACH 1: Recursion/D&Q. Set root to midpoint of l and r and recurse. */
BSTNode recurse(vector<int> list, int l, int r) {
    if (l > r) return NULL;
    int m = (l+r)/2;
    BSTNode root = new Node;
    root->val = list[m];
    root->left = recurse(list, l, m-1);
    root->right = recurse(list, m+1, r);
    return root;
}
BSTNode makeTree(vector<int> list) {
    return recurse(list, 0, list.size()-1);
}

int main(int argc, char **argv) {
    vector<int> list;
    for (int i = 1; i <= 12; i++) list.push_back(i);
    std::cout << assertBST(makeTree(list)) << '\n';
    printInorder(makeTree(list));
    std::cout << '\n';
    return 0;
}
