#include <iostream>
#include <string>
#include <vector>
#include <stack>
using namespace std;

/*

You are given the root of a binary tree. You need to implement 2 functions:

1. serialize(root) which serializes the tree into a string representation
2. deserialize(s) which deserializes the string back to the original tree that it represents

For this problem, often you will be asked to design your own serialization format. However, for 
simplicity, let's use the pre-order traversal of the tree.

     1
    / \
   3   4
  / \   \
 2   5   7

serialize(tree) -> # 1 3 2 # # 5 # # 4 # 7 # #
deserialize('# 1 3 2 # # 5 # # 4 # 7 # #') -> original tree
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
    TreeNode(int v, Node l, Node r) {
        val = v;
        left = l, right = r;
    }
};
void printInOrder(Node root) {
    if (root != NULL) {
        printInOrder(root->left);
        std::cout << root->val << ' ';
        printInOrder(root->right);
    }
}

vector<string> split(string str, string sep){
    char* cstr = const_cast<char*>(str.c_str());
    char* current;
    vector<string> arr;
    current = strtok(cstr, sep.c_str());
    while (current != NULL) {
        arr.push_back(current);
        current = strtok(NULL, sep.c_str());
    }
    return arr;
}

/* APPROACH 1: Regular preorder traversal for serialize. To process string, there are
a few cases: L+R leaf exist, one L or R leaf, and node itself is leaf. Should all be
O(N) */
string serialize(Node root) {
    if (root == NULL) return "";
    stack<Node> s;
    s.push(root);
    string preorder = "";
    while (!s.empty()) {
        Node t = s.top();
        s.pop();
        if (t == NULL) preorder.append("# ");
        else {
            preorder.append(to_string(t->val) + " ");
            s.push(t->right);
            s.push(t->left);
        }
    }
    return preorder.substr(0, preorder.length()-1);
}

Node deserializeAux(vector<string> preorder, int &i) {
    if (i >= preorder.size()) return NULL;
    if (preorder[i] == "#") return NULL;
    Node ans = new TreeNode(atoi(preorder[i].c_str()));
    i++;
    ans->left = deserializeAux(preorder, i);
    i++;
    ans->right = deserializeAux(preorder, i);
    return ans;
}
Node deserialize(string preorder) {
    int i = 0;
    vector<string> splitPreorder = split(preorder, " ");
    return deserializeAux(splitPreorder, i);
}

int main(int argc, char **argv) {
    Node tree = new TreeNode(1,
        new TreeNode(3, new TreeNode(2), new TreeNode(5)),
        new TreeNode(4, NULL, new TreeNode(7)));
    printInOrder(tree);
    std::cout << '\n';
    
    string serialized = serialize(tree);
    std::cout << serialized << '\n';
    
    Node deserialized = deserialize(serialized);
    printInOrder(deserialized);
    std::cout << '\n';
    return 0;
}
