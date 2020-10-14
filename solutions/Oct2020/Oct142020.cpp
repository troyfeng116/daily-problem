#include <iostream>
#include <vector>
using namespace std;

/*
A k-ary tree is a tree with k-children, and a tree is symmetrical if the data of the left side of the tree 
is the same as the right side of the tree.

Here's an example of a symmetrical k-ary tree.
        4
     /     \
    3        3
  / | \    / | \
9   4  1  1  4  9
Given a k-ary tree, figure out if the tree is symmetrical.
*/

typedef struct TreeNode *Node;
struct TreeNode { 
    int val; 
    vector<TreeNode*> children;
    TreeNode(int v) {
        val = v;
    }
};
void print(Node tree) {
    std::cout << tree->val << " ";
    for (int i = 0; i < tree->children.size(); i++) {
        print(tree->children[i]);
    }
}

/* APPROACH 1: Mirror (reverse) the tree and traverse to see if it is equal to its reflection. 
Runs in O(N) time and space. */
Node mirror(Node root) {
    Node newRoot = new TreeNode(root->val);
    vector<TreeNode*> mirroredChildren;
    for (int i = root->children.size()-1; i >= 0; i--) {
        mirroredChildren.push_back(mirror(root->children[i]));
    }
    newRoot->children = mirroredChildren;
    return newRoot;
}
bool isEqual(Node root1, Node root2) {
    if (root1->val != root2->val) return false;
    int k = root1->children.size();
    if (root2->children.size() != k) return false;
    for (int i = 0; i < k; i++) {
        if (!isEqual(root1->children[i], root2->children[i])) return false;
    }
    return true;
}
bool isSymmetrical(Node root) {
    if (root == NULL) return true;
    Node mirrored = mirror(root);
    std::cout << "MIRRORED: ";
    print(mirrored);
    std::cout << '\n';
    return isEqual(root, mirrored);
}

/* APPROACH 2: Recursion. Just O(N) time */
bool isSymmetrical2Aux(Node left, Node right) {
    if (left->val != right->val) return false;
    int k = left->children.size();
    if (right->children.size() != k) return false;
    for (int i = 0; i < k; i++) {
        if (!isSymmetrical2Aux(left->children[i], right->children[k-i-1])) return false;
    }
    std::cout << left->val << " and " << right->val << " good!\n";
    return true;
}
bool isSymmetrical2(Node root) {
    if (root == NULL) return true;
    int k = root->children.size();
    for (int i = 0; i < k; i++) {
        if (!isSymmetrical2Aux(root->children[i], root->children[k-i-1])) return false;
    }
    return true;
}

int main(int argc, char **argv) {
    Node test = new TreeNode(5);
    Node left = new TreeNode(3);
    left->children = {new TreeNode(9), new TreeNode(4), new TreeNode(1)};
    Node center = new TreeNode(18);
    center->children = {new TreeNode(11), new TreeNode(12), new TreeNode(11)};
    Node right = new TreeNode(3);
    right->children = {new TreeNode(1), new TreeNode(4), new TreeNode(9)};
    test->children = {left, center, right};
    print(test);
    std::cout << '\n';
    std::cout << isSymmetrical(test) << '\n';
    std::cout << isSymmetrical2(test) << '\n';
    return 0;
}
