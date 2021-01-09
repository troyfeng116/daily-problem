#include <iostream>
#include <string>
#include <stack>
using namespace std;

/*
Given a valid parenthesis string (with only '(' and ')', an open parenthesis will always
end with a close parenthesis, and a close parenthesis will never start first), remove
the outermost layers of the parenthesis string and return the new parenthesis string.

If the string has multiple outer layer parenthesis, i.e. (())(), remove all outer layers
and construct the new string. So in the example, the string can be broken down into
(()) + (). By removing both components outer layer we are left with () + '' which is
simply (), thus the answer for that input would be ().
*/

/* APPROACH 1: Stack, but skip first parenthesis and push onto stack until empty and
next char is the closing parenthesis. O(N) */
string removeOuterParentheses(string str) {
    stack<char> stk;
    string ans;
    for (int i = 1; i < str.length(); i++) {
        char c = str[i];
        if (stk.empty()) {
            if (c == ')') i++;
            else {
                ans += c;
                stk.push(c);
            }
        } else {
            ans += c;
            if (c == ')') stk.pop();
            else stk.push(c);
        }
    }
    return ans;
}

int main(int argc, char **argv) {
    string test = "(())()((())())(())";
    std::cout << removeOuterParentheses(test) << '\n';
    return 0;
}
