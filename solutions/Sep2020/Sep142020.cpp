#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
Given a binary tree, return all values given a certain height h.
*/

/* QUESTIONS: is height of tree >= h? Will assume yes */

typedef struct TreeNode *Node;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
};
Node createNode(int val) {
    Node ans = new TreeNode;
    ans->val = val;
    ans->left = NULL;
    ans->right = NULL;
    return ans;
}

/* APPROACH 1: BFS. Use a queue. Time and space O(N). */
vector<int> getValuesAtHeight(Node root, int h) {
    queue<Node> q;
    q.push(root);
    int h1 = 1;
    while (!q.empty() && h1 < h) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            Node n = q.front();
            if (n->left != NULL) q.push(n->left);
            if (n->right != NULL) q.push(n->right);
            q.pop();
        }
        h1++;
    }
    vector<int> ans;
    while (!q.empty()) {
        ans.push_back(q.front()->val);
        q.pop();
    }
    return ans;
}

int main(int argc, char **argv) {
    Node n[8];
    for (int i = 0; i < 8; i++) n[i] = createNode(i);
    n[4]->left = n[2];
    n[2]->left = n[1];
    n[1]->right = n[3];

    n[4]->right = n[6];
    n[6]->left = n[5];
    n[6]->right = n[7];
    vector<int> res = getValuesAtHeight(n[4], 3);
    for (int i = 0; i < res.size(); i++) {
        std::cout << res[i] << '\n';
    }
    return 0;
}
