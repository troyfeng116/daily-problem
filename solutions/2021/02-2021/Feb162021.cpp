#include <iostream>
using namespace std;

/*
Given a binary tree, flatten the binary tree using preorder traversal. Instead of creating a new list,
reuse the nodes, where the list is represented by following each right child. As such the root should
always be the first element in the list so you do not need to return anything in the implementation, 
just rearrange the nodes such that following the right child will give us the list.

ex.
      1
    /   \
   2     3
  /     /
 5     4

=>

   1
    \ 
     2
      \
       5
        \
         3
          \
           4
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
    TreeNode(int v, TreeNode *l, TreeNode *r) {
        val = v;
        left = l;
        right = r;
    }
};

void printPreorder(Node tree) {
    if (tree == nullptr) return;
    cout << tree->val << ' ';
    printPreorder(tree->left);
    printPreorder(tree->right);
}

/* APPROACH 1: DFS. Pass right-most node by reference.
At each recursion node:
-save right node
-if left node exists, move it to right node and flatten it
    -rightMost node moves along the nodes by reference
-if right node exists, attach it to rightMost node and flatten it
O(N) */
void dfs(Node &rightMost) {
    if (rightMost == nullptr) return;
    Node right = rightMost->right;
    if (rightMost->left != nullptr) {
        rightMost->right = rightMost->left;
        rightMost->left = nullptr;
        rightMost = rightMost->right;
        dfs(rightMost);
    }
    if (right != nullptr) {
        rightMost->right = right;
        rightMost = rightMost->right;
        dfs(rightMost);
    }
}
void flattenTree(Node tree) {
    return dfs(tree);
}

int main(int argc, char **argv) {
    Node tree = new TreeNode(1,
        new TreeNode(2, new TreeNode(5), nullptr),
        new TreeNode(3, new TreeNode(4), nullptr));
    flattenTree(tree);
    printPreorder(tree);
    cout << '\n';
    return 0;
}
