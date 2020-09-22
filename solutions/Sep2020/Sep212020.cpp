#include <iostream>
#include <vector>
using namespace std;

/*
You are given the root of a binary tree. Find and return the largest subtree of that tree, which 
is a valid binary search tree.
*/

typedef struct TreeNode *Node;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int v) {
        val = v;
        left = NULL;
        right = NULL;
    }
};

/* APPROACH 1: For each root, run inorder traversal and check if sorted. If yes, return length
through pointer. Else return max length of children recursively. O(N^2) time and space. */
bool isSorted(vector<int> arr) {
    for (int i = 0; i < arr.size()-1; i++) {
        if (arr[i] > arr[i+1]) return false;
    }
    return true;
}
void inorderAux(Node root, vector<int> &ans) {
    if (root->left != NULL) inorderAux(root->left, ans);
    ans.push_back(root->val);
    if (root->right != NULL) inorderAux(root->right, ans);
}
vector<int> inorder(Node root) {
    vector<int> ans;
    inorderAux(root, ans);
    return ans;
}
Node largestBSTAux(Node root, int *maxSize) {
    if (root == NULL) {
        *maxSize = 0;
        return NULL;
    }
    vector<int> arr = inorder(root);
    if (isSorted(arr)) {
        *maxSize = arr.size();
        return root;
    }
    if (root->left == NULL && root->right == NULL) {
        *maxSize = 1;
        return root;
    }
    if (root->left == NULL) {
        return largestBSTAux(root->right, maxSize);
    }
    if (root->right == NULL) {
        return largestBSTAux(root->left, maxSize);
    }
    Node biggestLeft = largestBSTAux(root->left, maxSize);
    int l = *maxSize;
    Node biggestRight = largestBSTAux(root->right, maxSize);
    int r = *maxSize;
    return l>r ? biggestLeft : biggestRight;
}
Node largestBST(Node root) {
    int maxSize = 0;
    return largestBSTAux(root, &maxSize);
}

/* APPROACH 2: use a struct to minimize complex pointer returns, bottom up recursion. O(N) */
struct returnInfo {
    int size;
    int min;
    int max;
    int maxSize;
    bool isBST;
    Node ans;
    returnInfo() {};
    returnInfo(int s, int m1, int m2, int ms, bool ib, Node n) {
        size = s;
        min = m1;
        max = m2;
        maxSize = ms;
        isBST = ib;
        ans = n;
    }
};
returnInfo largestBST2Aux(Node root) {
    if (root == NULL) {
        return returnInfo(0, INT_MAX, INT_MIN, 0, true, NULL);
    }
    if (root->left == NULL && root->right == NULL) {
        return returnInfo(1, root->val, root->val, 1, true, root);
    }
    returnInfo l = largestBST2Aux(root->left);
    returnInfo r = largestBST2Aux(root->right);
    returnInfo res;
    res.size = 1 + l.size + r.size;
    if (l.isBST && r.isBST && l.max < root->val && root->val < r.min) {
        res.min = min(l.min, min(r.min, root->val));
        res.max = max(r.max, max(l.max, root->val));
        res.maxSize = res.size;
        res.ans = root;
        res.isBST = true;
        return res;
    }
    res.maxSize = max(l.maxSize, r.maxSize);
    res.ans = l.maxSize > r.maxSize? l.ans : r.ans;
    res.isBST = false;
    return res;
}
Node largestBST2(Node root) {
    return largestBST2Aux(root).ans;
}

int main(int argc, char **argv) {
    Node root = new TreeNode(5);
    Node n1 = new TreeNode(6);
    Node n2 = new TreeNode(2);
    Node n3 = new TreeNode(7);
    Node n4 = new TreeNode(4);
    Node n5 = new TreeNode(9);
    root->left = n1;
    root->left->left = n2;
    root->right = n3;
    root->right->left = n4;
    root->right->right = n5;

    Node res = largestBST(root);
    vector<int> test = inorder(res);
    for (int i = 0; i < test.size(); i++) {
        std::cout << test[i] << " ";
    }
    std::cout << '\n';

    Node res2 = largestBST2(root);
    vector<int> test2 = inorder(res2);
    for (int i = 0; i < test2.size(); i++) {
        std::cout << test2[i] << " ";
    }
    std::cout << '\n';
    return 0;
}
