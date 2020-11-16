#include <iostream>
#include <unordered_map>
using namespace std;

/*
Given a binary tree, find the most frequent subtree sum.

Example:

   3
  / \
 1   -3

The above tree has 3 subtrees. The root node with 3, and the 2 leaf nodes, which gives us a total of 
3 subtree sums. The root node has a sum of 1 (3 + 1 + -3), the left leaf node has a sum of 1, and 
the right leaf node has a sum of -3. Therefore the most frequent subtree sum is 1.

If there is a tie between the most frequent sum, you can return any one of them.
*/

typedef struct TreeNode *Node;
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) {
        val = v;
        left = NULL, right = NULL;
    }
    TreeNode(int v, TreeNode *l, TreeNode *r) {
        val = v;
        left = l , right = r;
    }
};

/* APPROACH 1: DFS. Store in hashmap where (k,v) = (sum, freq). O(N) time + space */
int findSum(Node root, unordered_map<int, int> &table) {
    if (root == NULL) return 0;
    int left = findSum(root->left, table);
    int right = findSum(root->right, table);
    int sum = left + right + root->val;
    if (table[sum]) table[sum]++;
    else table[sum] = 1;
    return sum;
}
int mostFreqSum(Node root) {
    unordered_map<int, int> table;
    findSum(root, table);
    int maxFreq = 0, ans = 0;
    for (auto i = table.begin(); i != table.end(); i++) {
        if (i->second > maxFreq) {
            maxFreq = i->second;
            ans = i->first;
        }
    }
    return ans;
}

/* APPROACH 2: Same as approach 1, but reduce to 1 O(N) pass of hashmap. */
int findSum2(Node root, unordered_map<int, int> &table, int &maxFreq) {
    if (root == NULL) return 0;
    int left = findSum2(root->left, table, maxFreq);
    int right = findSum2(root->right, table, maxFreq);
    int sum = left + right + root->val;
    if (table[sum]) table[sum]++;
    else table[sum] = 1;
    maxFreq = max(maxFreq, table[sum]);
    return sum;
}
int mostFreqSum2(Node root) {
    unordered_map<int, int> table;
    int maxFreq = 0;
    findSum2(root, table, maxFreq);
    for (auto i = table.begin(); i != table.end(); i++) {
        if (i->second == maxFreq) {
            return i->first;
        }
    }
    return -1;
}

int main(int argc, char **argv) {
    Node root = new TreeNode(3, new TreeNode(-3), new TreeNode(1));
    std::cout << "APPROACH 1 TESTING: " << mostFreqSum(root) << '\n';
    std::cout << "APPROACH 2 TESTING: " << mostFreqSum2(root) << '\n';
    return 0;
}
