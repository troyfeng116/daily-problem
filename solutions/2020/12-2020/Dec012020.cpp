#include <iostream>
#include <vector>
using namespace std;

/*
Given a postorder traversal for a binary search tree, reconstruct the tree. A postorder traversal 
is a traversal order where the left child always comes before the right child, and the right child 
always comes before the parent for all nodes.
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

void print(Node root) {
    if (root == NULL) return;
    print(root->left);
    std::cout << root->val << " ";
    print(root->right);
}

/* APPROACH 1: Root node is always final node. Left subtree is always first half and right subtree
is second half, so right subtree starts at first node > root. Recurse for subtrees. O(N^2) */
int search(vector<int> postorder, int l, int r) {
    int m = l;
    while (m < r && postorder[m] < postorder[r]) m++;
    return m;
}
Node aux(vector<int> postorder, int l, int r) {
    if (l > r) return NULL;
    if (l == r) return new TreeNode(postorder[l]);
    int rootVal = postorder[r];
    Node root = new TreeNode(rootVal);
    int m = search(postorder, l, r);
    root->left = aux(postorder, l, m-1);
    root->right = aux(postorder, m, r-1);
    return root;
}
Node reconstructTree(vector<int> postorder) {
    return aux(postorder, 0, postorder.size()-1);
}

/* APPROACH 2: track postorder index in pointer and start from root at end of postorder. 
O(N) */
Node aux2(vector<int> postorder, int *postIndex, int key, int min, int max) {
    if (*postIndex < 0) return NULL;
    Node root = NULL;
    if (min < key && key < max) {
        root = new TreeNode(key);
        *postIndex = *postIndex - 1;
        if (*postIndex > 0) {
            root->right = aux2(postorder, postIndex, postorder[*postIndex], key, max);
            root->left = aux2(postorder, postIndex, postorder[*postIndex], min, key);
        }
    }
    return root;
}
Node reconstructTree2(vector<int> postorder) {
    int postIndex = postorder.size() - 1;
    return aux2(postorder, &postIndex, postorder[postIndex], INT_MIN, INT_MAX);
}

int main(int argc, char **argv) {
    vector<int> postorder = {1, 7, 5, 50, 40, 10};

    Node res1 = reconstructTree(postorder);
    std::cout << "APPROACH 1 TESTING: ";
    print(res1);
    std::cout << '\n';

    Node res2 = reconstructTree2(postorder);
    std::cout << "APPROACH 2 TESTING: ";
    print(res2);
    std::cout << '\n';
    return 0;
}
