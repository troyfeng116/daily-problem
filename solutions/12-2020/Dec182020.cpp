#include <iostream>
#include <vector>
using namespace std;

/*
Given a binary tree, find and return the largest path from root to leaf.

ex. 
    1
  /   \
 3     2
  \   /
   5 4
=> [1, 3, 5]
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
        left = l;
        right = r;
    }
};

void print(vector<int> arr) {
    if (arr.size() == 0) {
        std::cout << "[]\n";
        return;
    }
    std::cout << '[';
    for (int i = 0; i < arr.size() - 1; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[arr.size()-1] << "]\n";
}

/* APPROACH 1: recursion, DFS + backtracking. At each step, we need:
curNode, pathSum, path, &maxPathSum, &maxPath.
O(N), as each node is visited at most once */
void dfs(Node curNode, int pathSum, vector<int> &path, int &maxPathSum, vector<int> &maxPath) {
    if (curNode == NULL) return;
    if (curNode->left == NULL && curNode->right == NULL) {
        if (pathSum > maxPathSum) {
            maxPathSum = pathSum;
            maxPath = path;
        }
        return;
    }
    if (curNode->left != NULL) {
        path.push_back(curNode->left->val);
        dfs(curNode->left, pathSum + curNode->left->val, path, maxPathSum, maxPath);
        path.pop_back();
    }
    if (curNode->right != NULL) {
        path.push_back(curNode->right->val);
        dfs(curNode->right, pathSum + curNode->right->val, path, maxPathSum, maxPath);
        path.pop_back();
    }
}
vector<int> largestPath(Node root) {
    int maxPathSum = INT_MIN;
    vector<int> path, maxPath;
    path.push_back(root->val);
    dfs(root, root->val, path, maxPathSum, maxPath);
    return maxPath;
}

int main(int argc, char **argv) {
    Node root = new TreeNode(1,
        new TreeNode(3, NULL, new TreeNode(5)),
        new TreeNode(2, new TreeNode(4), NULL));
    vector<int> res = largestPath(root);
    print(res);
    return 0;
}
