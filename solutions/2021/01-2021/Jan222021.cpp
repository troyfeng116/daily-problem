#include <iostream>
#include <string>
#include <stack>
using namespace std;

/*
Given a string, we want to remove 2 adjacent characters that are the same, and repeat the process
with the new string until we can no longer perform the operation.

ex. "cabba" => "c"
*/

/* APPROACH 1: Brute force. While there are still 2 adjacent characters, remove each pair and repeat.
O(N^2) */
string removePairs(string s) {
    string ans = "";
    int n = s.length();
    for (int i = 0; i < n; i++) {
        if (i < n - 1 && s[i] == s[i+1]) i++;
        else ans += s[i];
    }
    return ans;
}
string removeAdjacentChars(string s) {
    string ans = s;
    while (ans.length() != (ans = removePairs(ans)).length()) {
        continue;
    }
    return ans;
}

/* APPROACH 2: Stack. Kinda like matching parentheses. O(N) */
string removeAdjacentChars2(string s) {
    stack<char> stk;
    int n = s.length();
    for (int i = 0; i < n; i++) {
        if (!stk.empty() && stk.top() == s[i]) stk.pop();
        else stk.push(s[i]);
    }
    string ans = "";
    while (!stk.empty()) {
        ans = stk.top() + ans;
        stk.pop();
    }
    return ans;
}

int main(int argc, char **argv) {
    string test = "cabbage";
    std::cout << "APPROACH 1 TESTING: " << removeAdjacentChars(test) << '\n';
    std::cout << "APPROACH 2 TESTING: " << removeAdjacentChars2(test) << '\n';
    return 0;
}
