#include <iostream>
#include <queue>
using namespace std;

/*
You are given a tree, and your job is to print it level-by-level with linebreaks.

    a
   / \
  b   c
 / \ / \
d  e f  g

The output should be
a
bc
defg
*/

typedef struct TreeNode *Node;
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) {
        val = v;
        left = NULL, right = NULL;
    }
    TreeNode(int v, TreeNode *l, TreeNode *r) {
        val = v;
        left = l, right = r;
    }
};

/* APPROACH 1: Recursion. Use recursive function to print level of tree. O(N^2) */
int height(Node root) {
    if (root == NULL) return 0;
    return max(height(root->left), height(root->right)) + 1;
}
void printLevel(Node root, int l) {
    if (root == NULL) return;
    if (l == 1) std::cout << root->val << " ";
    printLevel(root->left, l-1);
    printLevel(root->right, l-1);
}
void printTreeLevelOrder(Node root) {
    int h = height(root);
    for (int level = 1; level <= h; level++) {
        printLevel(root, level);
        std::cout << '\n';
    }
}

/* APPROACH 2: Queue-based level order traversal. O(N) time + space */
void printTreeLevelOrder2(Node root) {
    queue<Node> q;
    q.push(root);
    while (!q.empty()) {
        int size = q.size();
        for (int i = 0; i < size; i++) {
            Node t = q.front();
            q.pop();
            if (t->left) q.push(t->left);
            if (t->right) q.push(t->right);
            std::cout << t->val << " ";
        }
        std::cout << '\n';
    }
}

int main(int argc, char **argv) {
    Node root = new TreeNode(1,
        new TreeNode(2, new TreeNode(4), new TreeNode(5)),
        new TreeNode(3, new TreeNode(6), new TreeNode(7)));
    std::cout << "APPROACH 1 TESTING: \n";
    printTreeLevelOrder(root);
    std::cout << "APPROACH 2 TESTING: \n";
    printTreeLevelOrder2(root);
    return 0;
}
