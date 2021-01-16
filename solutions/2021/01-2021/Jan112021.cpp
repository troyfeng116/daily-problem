#include <iostream>
using namespace std;

/*
Given a binary search tree (BST) and a value s, split the BST into 2 trees, where one tree has all values less
than or equal to s, and the other tree has all values greater than s while maintaining the tree structure of
the original BST. You can assume that s will be one of the node's value in the BST. Return both trees' root
node as a tuple.
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
void print(Node root) {
    if (root == nullptr) return;
    print(root->left);
    std::cout << root->val << " ";
    print(root->right);
}

/* APPROACH 1: Iterative. */
void setChild(Node node, bool toLeft, Node child){
    // Assign child node to the indicated direction: left or right
    if (toLeft) {
        node->left = child;
    } else {
        node->right = child;
    }
}
pair<Node, Node> splitBST(Node root, int k) {
    Node originalRoot = root;
    Node root2 = nullptr, parent1 = nullptr, parent2 = nullptr;
    // Determine at which side of the root we will travel
    bool toLeft = root != nullptr && k < root->val;

    while (root != nullptr) {
        while (root != nullptr && (k < root->val) == toLeft) {
            parent1 = root;
            root = toLeft ? root->left : root->right;
        }
        setChild(parent1, toLeft, nullptr); // Cut out the edge. root is now detached
        toLeft = !toLeft; // toggle direction
        if (root2 == nullptr) {
            root2 = root; // This is the root of the other tree.
        } else if (parent2 != nullptr) {
            setChild(parent2, toLeft, root); // re-attach the detached subtree
        }
        parent2 = parent1;
        parent1 = nullptr;
    }
    return {originalRoot, root2};
}

/* APPROACH 2: Recursive. Each call returns {node1, node2}, where node1 is root of all nodes <= k
and node2 is root of all nodes > k for that subtree. */
pair<Node, Node> splitBST2(Node root, int k) {
    if (root == nullptr) {
        return {nullptr, nullptr};
    }
    if (root->val > k) {
        pair<Node, Node> l = splitBST2(root->left, k);
        root->left = l.second;
        return {l.first, root};
    } else {
        pair<Node, Node> r = splitBST2(root->right, k);
        root->right = r.first;
        return {root, r.second};
    }
}

int main(int argc, char **argv) {
    Node root1 = new TreeNode(3,
        new TreeNode(1, nullptr, new TreeNode(2)),
        new TreeNode(4, nullptr, new TreeNode(5)));
    std::cout << "-------- APPROACH 1 TESTING --------\n";
    pair<Node, Node> res = splitBST(root1, 2);
    print(res.first);
    std::cout << '\n';
    print(res.second);
    std::cout << '\n';

    Node root2 = new TreeNode(3,
        new TreeNode(1, nullptr, new TreeNode(2)),
        new TreeNode(4, nullptr, new TreeNode(5)));
    std::cout << "-------- APPROACH 2 TESTING --------\n";
    pair<Node, Node> res2 = splitBST2(root2, 2);
    print(res2.first);
    std::cout << '\n';
    print(res2.second);
    std::cout << '\n';
    return 0;
}