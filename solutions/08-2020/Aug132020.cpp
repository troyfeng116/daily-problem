#include <iostream>
using namespace std;

/*
You are given the root of a binary tree. Invert the binary tree in place. That is, all left children should become right children, and all right children should become left children.

Example:

    a
   / \
  b   c
 / \  /
d   e f

The inverted version of this tree is as follows:

  a
 / \
 c  b
 \  / \
  f e  d
*/

typedef struct Node* TreeNode;
struct Node {
	int val;
	Node *left;
	Node *right;
};

void insert(TreeNode *tree, int v) {
	if (*tree == NULL) {
		TreeNode newNode = new Node;
		newNode->val = v;
		newNode->left = NULL;
		newNode->right = NULL;
		*tree = newNode;
	}
	else if (v < (*tree)->val) {
		insert(&((*tree)->left), v);
	}
	else insert(&((*tree)->right), v);
}

void print(TreeNode *tree) {
	if (*tree == NULL) return;
	print(&((*tree)->left));
	std::cout << (*tree)->val;
	print(&((*tree)->right));
}

void reverse(TreeNode tree) {
	if (tree == NULL) return;
	TreeNode temp = tree->left;
	tree->left = tree->right;
	tree->right = temp;
	reverse(tree->left);
	reverse(tree->right);
}

int main(int argc, char **argv) {
	TreeNode tree = NULL;
	insert(&tree, 3);
	insert(&tree, 2);
	insert(&tree, 1);
	insert(&tree, 4);
	insert(&tree, 6);
	insert(&tree, 7);
	insert(&tree, 5);
	print(&tree);
	std::cout << "\n";
	reverse(tree);
	print(&tree);
	std::cout << "\n";
	return 0;
}
