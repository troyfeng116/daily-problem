#include <iostream>
using namespace std;

/*
You are given the root of a binary tree. Find the path between 2 nodes that maximizes the sum of all the 
nodes in the path, and return the sum. The path does not necessarily need to go through the root.

ex.
       *10
       /  \
     *2   *10
     / \     \
   *20  1    -25
             /  \
            3    4
should return 20 + 2 + 10 + 10 = 42.
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

/* APPROACH 1: For each node, there are 4 cases if that node is in the max path sum:
1. Max path sum is only that node.
2. Max path sum is max path through L child + node.
3. Max path sum is max path through R child + node.
4. Max path sum is max path through L child + node + max path through R child.
Case 4 is unique, because it would mean the path can't go to any of node's ancestors. So we want to pass
the max of case(1,2,3) back up to the ancestor, but also consider 4 in our final answer.
In recursive call on node, we return max path sum including node as well as overall max path
sum result. Pass result as reference, return max path sum going through node.
O(N) DFS
*/
int maxPathSumAux(Node root, int &overallMaxPathSum) {
    if (root == NULL) return 0;
    int l = maxPathSumAux(root->left, overallMaxPathSum);
    int r = maxPathSumAux(root->right, overallMaxPathSum);
    int maxPathThruHere = max(max(l,r) + root->val, root->val);
    int maxPathEndingHere = max(maxPathThruHere, l + root->val + r);
    overallMaxPathSum = max(overallMaxPathSum, maxPathEndingHere);
    return maxPathThruHere;
}
int maxPathSum(Node root) {
    int res = INT_MIN;
    maxPathSumAux(root, res);
    return res;
}

int main(int argc, char **argv) {
    Node tree = 
        new TreeNode(10,
            new TreeNode(2, new TreeNode(20), new TreeNode(1)),
            new TreeNode(10,
                NULL,
                new TreeNode(-25, new TreeNode(3), new TreeNode(4))));
    int res = maxPathSum(tree);
    std::cout << res << '\n';
    return 0;
}
