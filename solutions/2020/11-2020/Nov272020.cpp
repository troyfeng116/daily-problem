#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

/*
Given a binary tree, return the list of node values in zigzag order traversal. Here's an example

Input:
        1
      /   \
     2     3
    / \   / \
   4   5 6   7

Output: [1, 3, 2, 4, 5, 6, 7]
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
    std::cout << "[";
    for (int i = 0; i < arr.size()-1; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[arr.size()-1] << "]\n";
}

/* APPROACH 1: Modified BFS with stack + queue. O(N) time + space */
vector<int> zigzagTraversal(Node root) {
    vector<int> ans;
    if (root == NULL) return ans;
    queue<Node> q;
    stack<int> s;
    q.push(root);
    bool reverse = false;
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            Node t = q.front();
            q.pop();
            if (reverse) s.push(t->val);
            else ans.push_back(t->val);
            if (t->left) q.push(t->left);
            if (t->right) q.push(t->right);
        }
        while (!s.empty()) {
            ans.push_back(s.top());
            s.pop();
        }
        reverse = !reverse;
    }
    return ans;
}

/* APPROACH 2: Modified BFS with deque. O(N) time + space */
vector<int> zigzagTraversal2(Node root) {
    vector<int> ans;
    if (root == NULL) return ans;
    deque<Node> dq;
    dq.push_back(root);
    bool popBack = false;
    while (!dq.empty()) {
        int size = dq.size();
        for (int i = 0; i < size; i++) {
            if (popBack) {
                Node t = dq.back();
                dq.pop_back();
                ans.push_back(t->val);
                if (t->right) dq.push_front(t->right);
                if (t->left) dq.push_front(t->left);
            }
            else {
                Node t = dq.front();
                dq.pop_front();
                ans.push_back(t->val);
                if (t->left) dq.push_back(t->left);
                if (t->right) dq.push_back(t->right);
            }
        }
        popBack = !popBack;
    }
    return ans;
}

int main(int argc, char **argv) {
    Node root = new TreeNode(1,
        new TreeNode(2, new TreeNode(4), new TreeNode(5)),
        new TreeNode(3, new TreeNode(6), new TreeNode(7)));

    std::cout << "APPROACH 1 TESTING: ";
    print(zigzagTraversal(root));
    std::cout << "APPROACH 2 TESTING: ";
    print(zigzagTraversal2(root));
    return 0;
}
