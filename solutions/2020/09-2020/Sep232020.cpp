#include <iostream>
#include <string>
#include <stack>
using namespace std;

/*
You are given a string of parenthesis. Return the minimum number of parenthesis that would need 
to be removed in order to make the string valid. "Valid" means that each open parenthesis has a 
matching closed parenthesis.

Example:
The following input should return 1.
"()())()"
*/

/* APPROACH 1: match parentheses using stack. O(N) time and space */
int minRemoveParentheses(string s) {
    stack<char> stack;
    int count = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s.at(i) == '(') stack.push(s.at(i));
        else if (stack.empty()) count++;
        else stack.pop();
    }
    return count + stack.size();
}

int main(int argc, char **argv) {
    string test = "()())(()))";
    std::cout << minRemoveParentheses(test) << '\n';
    return 0;
}
