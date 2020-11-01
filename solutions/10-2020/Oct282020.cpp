#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
Given the root of a binary tree, print its level-order traversal. For example:

  1
 / \
2   3
   / \
  4   5

The above tree should output 1, 2, 3, 4, 5.
*/

void print(vector<int> arr) {
	std::cout << "[";
	for (int i = 0; i < arr.size()-1; i++) {
		std::cout << arr[i] << ", ";
	}
	std::cout << arr[arr.size()-1] <<  "]\n";
}

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

/* APPROACH 1: Print level by level. O(N^2) worst case */
void getLevel(Node root, int level, vector<int> &ans) {
	if (root == NULL) ;
	else if (level == 1) ans.push_back(root->val);
	else {
		getLevel(root->left, level-1, ans);
		getLevel(root->right, level-1, ans);
	}
}
int height(Node root) {
	if (root->left == NULL && root->right == NULL) return 1;
	if (root->left == NULL) return 1 + height(root->right);
	if (root->right == NULL) return 1 + height(root->left);
	return max(height(root->left), height(root->right)) + 1;
}
vector<int> levelOrder(Node root) {
	vector<int> ans;
	int h = height(root);
	std::cout << h << '\n';
	for (int level = 1; level <= h; level++) {
		getLevel(root, level, ans);
	}
	return ans;
}

/* APPROACH 2: BFS. O(N) */
vector<int> levelOrder2(Node root) {
	vector<int> ans;
	if (root == NULL) return ans;
	queue<Node> q;
	q.push(root);
	while (!q.empty()) {
		Node t = q.front();
		q.pop();
		ans.push_back(t->val);
		if (t->left != NULL) q.push(t->left);
		if (t->right != NULL) q.push(t->right);
	}
	return ans;
}

int main(int argc, char **argv) {
	Node root = new TreeNode(1,
		new TreeNode(2),
		new TreeNode(3, new TreeNode(4), new TreeNode(5)));
	print(levelOrder(root));
	print(levelOrder2(root));
    return 0;
}
