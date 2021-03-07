#include <iostream>
#include <vector>
using namespace std;

/*
Given a tree, the leaves form a certain order from left to right. Two trees are considered
"leaf-similar" if their leaf orderings are the same.

ex. the following two trees are considered leaf-similar because their leaves are [2, 1]:

    3
   / \ 
  5   1
   \
    2 

    7
   / \ 
  2   1
   \
    2 

Determine, given two trees, whether they are "leaf similar."
*/

typedef struct TreeNode* Node;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode (int v) {
        val = v;
        left = nullptr;
        right = nullptr;
    }
    TreeNode(int v, TreeNode *l, TreeNode *r) {
        val = v;
        left = l;
        right = r;
    }
};

/* APPROACH 1: DFS inorder traversal to get leaves of each tree. O(M + N) */
void dfs(Node node, vector<int> &leaves) {
    if (node == nullptr) return;
    if (node->left == nullptr && node->right == nullptr) {
        leaves.push_back(node->val);
    }
    dfs(node->left, leaves);
    dfs(node->right, leaves);
}
bool areLeafSimilar(Node tree1, Node tree2) {
    vector<int> tree1Leaves;
    dfs(tree1, tree1Leaves);
    vector<int> tree2Leaves;
    dfs(tree2, tree2Leaves);
    return tree1Leaves == tree2Leaves;
}

int main(int argc, char **argv) {
    Node tree1 = new TreeNode(1,
        new TreeNode(5, nullptr, new TreeNode(2)),
        new TreeNode(1));
    Node tree2 = new TreeNode(7,
        new TreeNode(2, nullptr, new TreeNode(2)),
        new TreeNode(1));
    
    cout << areLeafSimilar(tree1, tree2) << '\n';
    return 0;
}
