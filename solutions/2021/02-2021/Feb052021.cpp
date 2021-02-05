#include <iostream>
#include <vector>
#include <string>
#include <stack>
using namespace std;

/*
Given a number n, generate all possible combinations of n well-formed brackets.

ex.
n = 3 -> ["((()))", "(()())", "()(())", "()()()", "(())()"]
*/

void print(vector<string> arr) {
    if (arr.size() == 0) {
        cout << "[]\n";
        return;
    }
    cout << "[";
    for (int i = 0; i < arr.size() - 1; i++) {
        cout << arr[i] << ", ";
    }
    cout << arr.back() << "]\n";
}

/* APPROACH 1: DFS. Pass # of open and close parentheses. If #open < n, next could be open.
If #open > #closed, next could be closed. If #open and #close = n and we followed those
rules, we will have balanced brackets. Exponential time */
void dfs(string str, int open, int closed, int n, vector<string> &ans) {
    if (closed == n) {
        ans.push_back(str);
        return;
    }
    if (open < n) dfs(str + '(', open + 1, closed, n, ans);
    if (open > closed) dfs(str + ')', open, closed + 1, n, ans);
}
vector<string> generateBrackets(int n) {
    vector<string> ans;
    dfs("", 0, 0, n, ans);
    return ans;
}

int main(int argc, char **argv) {
    print(generateBrackets(3));
    return 0;
}
