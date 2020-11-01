#include <iostream>
#include <vector>
using namespace std;

/*
You are given the root of a binary search tree. Return true if it is a valid 
binary search tree, and false otherwise. Recall that a binary search tree 
has the property that all values in the left subtree are less than or equal 
to the root, and all values in the right subtree are greater than or equal 
to the root.
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

/* APPROACH 1: Recursion. Each node visited once: O(N) time */
bool aux(Node root, int min, int max) {
    if (root == NULL) return true;
    if (root->val < min || root->val > max) return false;
    return aux(root->left, min, root->val) && aux(root->right, root->val, max);
}
bool isValidBST(Node root) {
    return aux(root, INT_MIN, INT_MAX);
}

/* APPROACH 2: Check if inorder traversal is sorted. O(N) time and space. */
void inorder(Node root, vector<int> *ans) {
    if (root == NULL) ;
    else {
        inorder(root->left, ans);
        (*ans).push_back(root->val);
        inorder(root->right, ans);
    }
}
bool isValidBST2(Node root) {
    vector<int> arr;
    inorder(root, &arr);
    for (int i = 0; i < arr.size()-1; i++) {
        if (arr[i] > arr[i+1]) return false;
    }
    return true;
}


int main(int argc, char **argv) {
    Node n1 = createNode(1);
    Node n2 = createNode(2);
    Node n3 = createNode(3);
    Node n4 = createNode(4);
    Node n5 = createNode(5);
    Node n6 = createNode(6);
    Node n7 = createNode(7);
    Node n8 = createNode(8);

    n3->left = n2;
    n2->left = n1;
    n3->right = n5;
    n5->left = n4;
    n5->right = n7;
    n7->left = n6;
    n7->right = n8;
    std::cout << isValidBST(n3) << '\n';
    std::cout << isValidBST2(n3) << '\n';
    return 0;
}
