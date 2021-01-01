#include <iostream>
#include <vector>
using namespace std;

/*
Given a tree, find if the binary tree is height balanced or not. A height balanced binary tree is a tree 
where every node's 2 subtree do not differ in height by more than 1.
*/

typedef struct TreeNode *Node;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int v) {
        val = v;
        left = NULL, right = NULL;
    }
    TreeNode(int v, TreeNode *l, TreeNode *r) {
        val = v;
        left = l, right = r;
    }
};

/* APPROACH 1: DFS to find height of L and R. Compare heights and compute height of root. O(N^2) */
int dfs(Node root) {
    if (root == NULL) return 0;
    int l = dfs(root->left);
    int r = dfs(root->right);
    if (l < 0 || r < 0) return -1;
    if (abs(l - r) > 1) return -1;
    return max(l, r) + 1;
}
bool isBalanced(Node root) {
    int res = dfs(root);
    if (res < 0) return false;
    return true;
}

/* APPROACH 2: DFS like approach 1 but with extra pass by reference argument. O(N) */
bool dfs2(Node root, int *height) {
    if (root == NULL) {
        *height = 0;
        return true;
    }
    int lh = 0, rh = 0;
    bool l = dfs2(root->left, &lh);
    bool r = dfs2(root->right, &rh);
    *height = max(lh, rh) + 1;
    if (abs(lh - rh) > 1) return false;
    return l && r;
}
bool isBalanced2(Node root) {
    int height = 0;
    return dfs2(root, &height);
}

int main(int argc, char **argv) {
    Node root = new TreeNode(1,
        new TreeNode(2, new TreeNode(4), NULL),
        new TreeNode(3));
    std::cout << "APPROACH 1 TESTING: " << isBalanced(root) << '\n';
    std::cout << "APPROACH 2 TESTING: " << isBalanced2(root) << '\n';
    return 0;
}
