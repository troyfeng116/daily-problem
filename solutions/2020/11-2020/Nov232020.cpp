#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
Given a binary tree and a given node value, return all of the node's cousins. Two nodes are 
considered cousins if they are on the same level of the tree with different parents. You can 
assume that all nodes will have their own unique value.

ex. findCousins(root, 5) => [4,6]
     1
    / \
   2   3
  / \   \
 4   6   5
*/

typedef struct TreeNode *Node;
struct TreeNode {
    int val;
    Node left;
    Node right;
    TreeNode(int v) {
        val = v;
        left = NULL, right = NULL;
    }
    TreeNode(int v, Node l, Node r) {
        val = v;
        left = l, right = r;
    }
};

void print(vector<int> arr) {
    std::cout << "[";
    for (int i = 0; i < arr.size()-1; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[arr.size()-1] << "]\n";
}

/* APPROACH 1: searchNode DFS returns pair with depth level containing target and parent node to
target.
Then DFS again and return all children on same level with dfs except for children of parent.
O(N^2) */
void findLevelAndParent(Node root, int target, int level, int parent, pair<int, int> &ans) {
    if (root == NULL) return;
    if (root->val == target) {
        ans.first = level;
        ans.second = parent;
        return;
    }
    findLevelAndParent(root->left, target, level+1, root->val, ans);
    findLevelAndParent(root->right, target, level+1, root->val, ans);
}
void dfs(Node root, int level, int parent, vector<int> &ans) {
    if (level < 0 || root == NULL || root->val == parent) ;
    else if (level == 0) {
        ans.push_back(root->val);
    }
    else {
        dfs(root->left, level-1, parent, ans);
        dfs(root->right, level-1, parent, ans);
    }
}
vector<int> findCousins(Node root, int target) {
    pair<int, int> pairRes{0, 0};
    findLevelAndParent(root, target, 0, -1, pairRes);
    vector<int> ans;
    dfs(root, pairRes.first, pairRes.second, ans);
    return ans;
}

/* APPROACH 2: BFS. O(N) time + space */
vector<int> findCousins2(Node root, int target) {
    queue<Node> q;
    vector<int> ans;
    if (root == NULL || root->val == target) return ans;
    q.push(root);
    bool found = false;
    // At start of every iteration, one entire level is in the queue.
    // If any children in the next level are the target, mark found and return next level sans target and sibling.
    while (!q.empty()) {
        int size = q.size();
        if (found) {
            for (int i = 0; i < size; i++) {
                ans.push_back(q.front()->val);
                q.pop();
            }
        }
        else {
            for (int i = 0; i < q.size(); i++) {
                Node t = q.front();
                q.pop();
                if (t->left && t->right) {
                    if (t->left->val == target || t->right->val == target) found = true;
                    else {
                        q.push(t->left);
                        q.push(t->right);
                    }
                }
                else if (t->left) {
                    if (t->left->val == target) found = true;
                    else q.push(t->left);
                }
                else if (t->right) {
                    if (t->right->val == target) found = true;
                    else q.push(t->right);
                }
            }
        }
    }
    return ans;
}

int main(int argc, char **argv) {
    Node root = new TreeNode(1,
        new TreeNode(2, new TreeNode(4), new TreeNode(6)),
        new TreeNode(3, NULL, new TreeNode(5)));
    std::cout << "APPROACH 1 TESTING:";
    print(findCousins(root, 5));

    std::cout << "APPROACH 2 TESTING: ";
    print(findCousins2(root, 5));
    return 0;
}
