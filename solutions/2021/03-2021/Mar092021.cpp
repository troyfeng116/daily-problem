#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/*
Given a binary tree, perform an in-order traversal both recursively and iteratively.
*/

void print(vector<int> arr) {
    if (arr.size() == 0) {
        cout << "[]\n";
        return;
    }
    cout << "[";
    for (int i = 0; i < arr.size() - 1; i++) {
        cout << arr[i] << ", ";
    }
    cout << arr.back() << "]\n";
}

typedef struct TreeNode *Node;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int v) {
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

/* APPROACH 1: recursive. O(N) */
void dfs(Node n, vector<int> &ans) {
    if (n == nullptr) return;
    dfs(n->left, ans);
    ans.push_back(n->val);
    dfs(n->right, ans);
}
vector<int> inorderRecursive(Node tree) {
    vector<int> ans;
    dfs(tree, ans);
    return ans;
}

/* APPROACH 2: iterative with stack. O(N) time + space */
vector<int> inorderIterative(Node tree) {
    stack<Node> stk;
    vector<int> ans;
    Node cur = tree;
    while (cur != nullptr || !stk.empty()) {
        while (cur != nullptr) {
            stk.push(cur);
            cur = cur->left;
        }
        cur = stk.top();
        stk.pop();
        ans.push_back(cur->val);
        cur = cur->right;
    }
    return ans;
}

int main(int argc, char **argv) {
    Node tree = new TreeNode(12,
        new TreeNode(6, new TreeNode(2), new TreeNode(7)),
        new TreeNode(15, new TreeNode(13), new TreeNode(20)));
    print(inorderRecursive(tree));
    print(inorderIterative(tree));
    return 0;
}