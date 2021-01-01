#include <iostream>
using namespace std;

/*
Given an integer k and a binary search tree, find the floor (less than or equal to) of k, and the 
ceiling (larger than or equal to) of k. If either does not exist, then print them as None.
*/

/*
Let's think about ceil first.
Run normal search in BST.
If k == node.val, return k.
If k > node.val
	Search right (ceil can't be node or anything in node.left)
If k < node.val
	If node.left == null, return node
	Else return largest value in node.left

If k is larger than any node in node.val, we will eventually hit right child of right-most node, and our
*t == NULL condition will handle it.
Similar for floor.
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

/* Return smallest element >= k in tree (CEILING). */
int searchCeil(Tree *t, int k) {
	if (*t == NULL) {
		return INT_MIN;
	}
	if (k == (*t)->val) return k;
	if (k > (*t)->val) {
		return searchCeil(&((*t)->right), k);
	}
	int possible = searchCeil(&((*t)->left), k);
	return possible >= k? possible: (*t)->val;
}

/* Return largest element <= k in tree (FLOOR). */
int searchFloor(Tree *t, int k) {
	if (*t == NULL) {
		return INT_MAX;
	}
	if (k == (*t)->val) return k;
	if (k < (*t)->val) {
		return searchFloor(&((*t)->left), k);
	}
	int possible = searchFloor(&((*t)->right), k);
	return possible <= k? possible: (*t)->val;
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
	std::cout << searchFloor(&tree, 8) << " " << searchCeil(&tree, 8) << '\n';
	return 0;
}
