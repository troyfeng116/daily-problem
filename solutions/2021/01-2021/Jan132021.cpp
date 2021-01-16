#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/*
Given a binary tree, find all duplicate subtrees (subtrees with the same value and same structure) and return them as
a list of lists [subtree1, subtree2, ...] where subtree1 is a duplicate of subtree2 etc.

ex.
     1
    / \
   2   2
  /   /
 3   3

-> [[(3), (3)], [(2, (3)), (2, (3))]]; the leaf (3) is duplicated and the subtree (2, 3) is duplicated.
*/

typedef struct TreeNode *Node;
struct TreeNode {
    int val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(int v) {
        val = v;
        left = nullptr, right = nullptr;
    }
    TreeNode (int v, TreeNode *l, TreeNode *r) {
        val = v;
        left = l, right = r;
    }
};

void printOneList(vector<string> list) {
    if (list.size() == 0) {
        std::cout << "[]\n";
        return;
    }
    std::cout << "[";
    for (int i = 0; i < list.size() - 1; i++) {
        std::cout << list[i] << ", ";
    }
    std::cout << list[list.size() - 1] << "]";
}
void print(vector<vector<string> > list) {
    if (list.size() == 0) {
        std::cout << "[]\n";
        return;
    }
    std::cout << "[";
    for (int i = 0; i < list.size() - 1; i++) {
        printOneList(list[i]);
        std::cout << ", ";
    }
    printOneList(list[list.size() - 1]);
    std::cout << "]\n";
}

/* APPROACH 1: an inorder traversal with markers for nullptr uniquely identifies a tree by value and structure.
Store (k,v) in map, where k = inorder traversal strings and v = count of nodes with that inorder traversal string,
and return list of value set of map. O(N) */
string inorder(Node root, unordered_map<string, int> &map) {
    if (root == nullptr) return "";
    string ans = "(";
    ans += inorder(root->left, map);
    ans += to_string(root->val);
    ans += inorder(root->right, map);
    ans += ")";
    if (map.find(ans) == map.end()) {
        map[ans] = 0;
    }
    map[ans]++;
    return ans;
}
vector<vector<string> > findDuplicateSubtrees(Node root) {
    unordered_map<string, int> map;
    inorder(root, map);
    vector<vector<string> > ans;
    for (auto it = map.begin(); it != map.end(); it++) {
        if (it->second > 1) ans.push_back(vector<string>(it->second, it->first));
    }
    return ans;
}

int main(int argc, char**argv) {
    Node root = new TreeNode(1,
        new TreeNode(2, new TreeNode(3), nullptr),
        new TreeNode(2, new TreeNode(3), nullptr));
    vector<vector<string> > res = findDuplicateSubtrees(root);
    print(res);
    return 0;
}
