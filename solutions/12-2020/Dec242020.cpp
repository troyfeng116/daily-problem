#include <iostream>
#include <queue>
using namespace std;

/*
Given a binary tree, find the level in the tree where the sum of all nodes on that level is the greatest.

ex.
    1          Level 0 - Sum: 1  
   / \
  4   5        Level 1 - Sum: 9 
 / \ / \
3  2 4 -1      Level 2 - Sum: 8

=> 1
*/

typedef struct TreeNode *Node;
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) {
        val = v;
        left = nullptr, right = nullptr;
    }
    TreeNode(int v, TreeNode *l, TreeNode *r) {
        val = v;
        left = l, right = r;
    }
};

/* APPROACH 1: Recursion. Find sum at each level. O(N^2) time */
int height(Node root) {
    if (root == nullptr) return 0;
    return 1 + max(height(root->left), height(root->right));
}
int sumAtLevel(Node root, int level) {
    if (root == nullptr) return 0;
    if (level == 0) return root->val;
    return sumAtLevel(root->left, level - 1) + sumAtLevel(root->right, level - 1);
}
int maxLevelSum(Node root) {
    int h = height(root);
    int maxSum = INT_MIN, maxLevel = 0;
    for (int level = 0; level < h; level++) {
        int sum = sumAtLevel(root, level);
        if (sum > maxSum) {
            maxSum = sum;
            maxLevel = level;
        }
    }
    return maxLevel;
}

/* APPROACH 2: BFS. O(N) time + space */
int maxLevelSum2(Node root) {
    if (root == nullptr) return 0;
    queue<Node> q;
    q.push(root);
    int maxSum = INT_MIN, maxLevel = 0, level = 0;
    while (!q.empty()) {
        int size = q.size();
        int sum = 0;
        for (int i = 0; i < size; i++) {
            Node t = q.front();
            q.pop();
            sum += t->val;
            if (t->left) q.push(t->left);
            if (t->right) q.push(t->right);
        }
        if (sum > maxSum) {
            maxSum = sum;
            maxLevel = level;
        }
        level++;
    }
    return maxLevel;
}

int main(int argc, char **argv) {
    Node root = new TreeNode(1,
        new TreeNode(4, new TreeNode(3), new TreeNode(2)),
        new TreeNode(5, new TreeNode(4), new TreeNode(-1)));
    
    std::cout << "APPROACH 1 TESTING: " << maxLevelSum(root) << '\n';
    std::cout << "APPROACH 2 TESTING: " << maxLevelSum2(root) << '\n';
    return 0;
}
