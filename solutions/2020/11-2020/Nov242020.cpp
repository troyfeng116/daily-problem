#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
Given a number n, generate all binary search trees that can be constructed with nodes 1 to n.
*/

typedef struct TreeNode *Node;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode (int v) {
        val = v;
        left = NULL, right = NULL;
    }
    TreeNode (int v, TreeNode *l, TreeNode *r) {
        val = v;
        left = l, right = r;
    }
};

void printPreorder(Node root) {
    queue<Node> q;
    q.push(root);
    while (!q.empty()) {
        Node t = q.front();
        q.pop();
        std::cout << t->val << " ";
        if (t->left) q.push(t->left);
        if (t->right) q.push(t->right);
    }
    std::cout << "\n";
}

/* APPROACH 1: Split [l,r] into [l,m) and (m,r] and recursively generate all subtrees for those
halves. Then combine all combos of those subtrees with new TreeNode(m). */
vector<Node> dfs(int l, int r) {
    vector<Node> list;
    if (l > r) {
        list.push_back(NULL);
        return list;
    }
    for (int m = l; m <= r; m++) {
        vector<Node> leftList = dfs(l, m-1);
        vector<Node> rightList = dfs(m+1, r);
        for (int i = 0; i < leftList.size(); i++) {
            Node left = leftList[i];
            for (int j = 0; j < rightList.size(); j++) {
                Node right = rightList[j];
                Node root = new TreeNode(m);
                root->left = left;
                root->right = right;
                list.push_back(root);
            }
        }
    }
    return list;
}
vector<Node> generateTrees(int n) {
    return dfs(1, n);
}

int main(int argc, char **argv) {
    vector<Node> res = generateTrees(3);
    for (int i = 0; i < res.size(); i++) printPreorder(res[i]);
    return 0;
}
