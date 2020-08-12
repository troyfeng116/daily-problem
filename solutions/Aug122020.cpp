#include <iostream>
using namespace std;

/*
Given an integer k and a binary search tree, find the floor (less than or equal to) of k, and the 
ceiling (larger than or equal to) of k. If either does not exist, then print them as None.
*/

typedef struct TreeNode* Tree;
struct TreeNode {
	int val;
	TreeNode *left;
	TreeNode *right;
};

void insert(Tree *t, int val) {
	if (*t == NULL) {
		Tree newNode = new TreeNode;
		newNode->val = val;
		newNode->left = NULL;
		newNode->right = NULL;
		*t = newNode;
	}
	else if (val < (*t)->val) insert(&((*t)->left), val);
	else insert(&((*t)->right), val);
}

void print(Tree t) {
	if (t == NULL) return;
	print(t->left);
	std::cout << t->val << " ";
	print(t->right);
}

int main(int argc, char **argv) {
	Tree tree = NULL;
	insert(&tree,3);
	insert(&tree,5);
	insert(&tree,1);
	insert(&tree,2);
	insert(&tree,7);
	print(tree);
	std::cout << "\n";
	return 0;
}
