#include <iostream>
#include <queue>
using namespace std;

/*
You are given the root of a binary tree. Find the level for the binary tree with the minimum sum, and 
return that value.

For instance, in the example below, the sums of the levels are 10, 2 + 8 = 10, and 4 + 1 + 2 = 7. So, 
the answer here should be 7.

     10
    /  \
   2    8
  / \    \
 4   1    2
*/

typedef struct TreeNode *Node;
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) {
        val = v, left = NULL, right = NULL;
    }
    TreeNode(int v, TreeNode *l, TreeNode *r) {
        val = v, left = l, right = r;
    }
};

/* APPROACH 1: Find all nodes at one level recursively, add by passing answer. O(N^2) */
int getHeight(Node root) {
    if (root == NULL) return 0;
    return max(getHeight(root->left), getHeight(root->right)) + 1;
}
int dfs(Node cur, int k) {
    if (cur == NULL) return 0;
    if (k == 1) return cur->val;
    return dfs(cur->left, k-1) + dfs(cur->right, k-1);
}
int minLevelSum(Node root) {
    if (root == NULL) return 0;
    int h = getHeight(root);
    int ans = INT_MAX;
    for (int level = 1; level <= h; level++) ans = min(ans, dfs(root, level));
    return ans;
}

/* APPROACH 2: BFS with queue. O(N) time + space */
int minLevelSum2(Node root) {
    if (root == NULL) return 0;
    queue<Node> q;
    q.push(root);
    int ans = INT_MAX;
    while (!q.empty()) {
        int size = q.size();
        int levelSum = 0;
        for (int i = 0; i < size; i++) {
            Node e = q.front();
            q.pop();
            levelSum += e->val;
            if (e->left) q.push(e->left);
            if (e->right) q.push(e->right);
        }
        ans = min(ans, levelSum);
    }
    return ans;
}

int main(int argc, char **argv) {
    Node root = new TreeNode(10,
        new TreeNode(2, new TreeNode(4), new TreeNode(1)),
        new TreeNode(8, NULL, new TreeNode(2)));
    std::cout << "APPROACH 1: " <<minLevelSum(root) << '\n';
    std::cout << "APPROACH 2: " << minLevelSum2(root) << '\n';
    return 0;
}
