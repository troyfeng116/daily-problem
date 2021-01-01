#include <iostream>
#include <vector>
using namespace std;

/* ----- Merry Christmas! ----- */

/*
Given 2 binary trees t and s, find if s has an equal subtree in t, where the structure and the
values are the same. Return True if it exists, otherwise return False.

ex.
Tree t:
    1
   / \
  4   5 
 / \ / \
3  2 4 -1

Tree s:
  4 
 / \
3   2 

findSubtree(s, t) => true
*/

/* QUESTION: are leaves included? Will assume yes. */

typedef struct TreeNode *Node;
struct TreeNode {
    int val;
    TreeNode *left, *right;
    TreeNode(int v) {
        val = v;
        left = nullptr, right = nullptr;
    }
    TreeNode(int v, Node l, Node r) {
        val = v;
        left = l, right = r;
    }
};

// KMT pattern matching.
vector<int> KMTHelper(vector<char> pattern) {
    // Returns lps[], where lps[i] = longest proper prefix of pattern[0,i] that is also
    // a suffix of pattern[0,i].
    int m = pattern.size();
    vector<int> lps(m, 0);
    int len = 0;
    int i = 1;
    while (i < m) {
        if (pattern[i] == pattern[len]) {
            len++;
            lps[i] = len;
            i++;
        } else {
            if (len != 0) len = lps[len-1];
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
    return lps;
}
bool isSubarr(vector<char> pattern, vector<char> text) {
    int m = pattern.size(), n = text.size();
    vector<int> lps = KMTHelper(pattern);
    int i = 0, j = 0;
    while (i < n) {
        if (text[i] == pattern[j]) {
            i++;
            j++;
        }
        if (j == m) {
            return true;
        } else if (i < n && text[i] != pattern[j]) {
            if (j != 0) j = lps[j - 1];
            else i++;
        }
    }
    return false;
}

/* APPROACH 1: Recursion. O(M*N), where M = #nodes in s, N = #nodes in t */
bool isEqual(Node s, Node t) {
    if (t == nullptr && s == nullptr) return true;
    if (t == nullptr || s == nullptr) return false;
    return s->val == t->val && isEqual(s->left, t->left) && isEqual(s->right, t->right);
}
bool findSubtree(Node s, Node t) {
    if (s == nullptr) return true;
    if (t == nullptr) return false;
    if (isEqual(t, s)) return true;
    return findSubtree(s, t->left) || findSubtree(s, t->right);
}

/* APPROACH 2: store inorder + preorder traversals in vector, marking nullptr with special
character. Then search for subarrays using KMT pattern matching. O(N) time + space */
void inorder(Node n, vector<char> &arr) {
    if (n == nullptr) arr.push_back('#');
    else {
        inorder(n->left, arr);
        arr.push_back(n->val + '0');
        inorder(n->right, arr);
    }
}
void preorder(Node n, vector<char> &arr) {
    if (n == nullptr) arr.push_back('#');
    else {
        arr.push_back(n->val + '0');
        preorder(n->left, arr);
        preorder(n->right, arr);
    }
}
bool findSubtree2(Node s, Node t) {
    if (s == nullptr) return true;
    if (t == nullptr) return false;
    vector<char> sInorder, tInorder;
    inorder(s, sInorder);
    inorder(t, tInorder);
    if (!isSubarr(sInorder, tInorder)) return false;
    vector<char> sPreorder, tPreorder;
    preorder(s, sPreorder);
    preorder(t, tPreorder);
    return isSubarr(sPreorder, tPreorder);
}

int main(int argc, char **argv) {
    Node s = new TreeNode(4, new TreeNode(3), new TreeNode(2));
    Node t = new TreeNode(1,
        new TreeNode(4, new TreeNode(3), new TreeNode(2)),
        new TreeNode(5, new TreeNode(4), new TreeNode(-1)));
    
    std::cout << "APPROACH 1 TESTING: " << findSubtree(s, t) << '\n';
    std::cout << "APPROACH 2 TESTING: " << findSubtree2(s, t) << '\n';
    return 0;
}