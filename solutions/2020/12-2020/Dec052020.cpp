#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/*
Given an expression (as a list) in reverse polish notation, evaluate the expression. Reverse polish notation is 
where the numbers come before the operand. Note that there can be the 4 operands '+', '-', '*', '/'. You can also 
assume the expression will be well formed.

Example
Input: [1, 2, 3, '+', 2, '*', '-']
Output: -9
The equivalent expression of the above reverse polish notation would be (1 - ((2 + 3) * 2)).
*/

typedef struct TreeNode *Node;
struct TreeNode {
    string val;
    TreeNode *left;
    TreeNode *right;
    TreeNode(string c) {
        val = c;
        left = NULL, right = NULL;
    }
    TreeNode(string c, TreeNode *l, TreeNode *r) {
        val = c;
        left = l, right = r;
    }
};

/* APPROACH 1: Stack. O(N) time + space */
int eval(string op, int x, int y) {
    if (op == "+") return x + y;
    if (op == "-") return x - y;
    if (op == "*") return x * y;
    if (op == "/") return x / y;
    std::cout << "Operation \"" << op << "\" not defined\n";
    return -1;
}
int evalReversePolish(vector<string> list) {
    if (list.size() == 0) return 0;
    stack<int> stk;
    for (int i = 0; i < list.size(); i++) {
        if (list[i] == "+" || list[i] == "-" || list[i] == "*" || list[i] == "/") {
            int y = stk.top();
            stk.pop();
            int x = stk.top();
            stk.pop();
            stk.push(eval(list[i], x, y));
        }
        else stk.push(stoi(list[i]));
    }
    return stk.top();
}

/* APPROACH 2: Recursion. Recursively peel away final element. O(N) */
int evalReversePolish2(vector<string> &list) {
    string op = list.back();
    list.pop_back();
    if (op != "+" && op != "-" && op != "*" && op != "/") return stoi(op);
    int y = evalReversePolish2(list);
    int x = evalReversePolish2(list);
    return eval(op, x, y);
}

int main(int argc, char **argv) {
    vector<string> list = {"1", "2", "3", "+", "2", "*", "-"};
    std::cout << "APPROACH 1 TESTING: " << evalReversePolish(list) << '\n';
    std::cout << "APPROACH 2 TESTING: " << evalReversePolish2(list) << '\n';
    return 0;
}
