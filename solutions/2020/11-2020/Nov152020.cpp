#include <iostream>
#include <string>
#include <stack>
using namespace std;

/*
Given a string with only ( and ), find the minimum number of characters to add or subtract to fix 
the string such that the brackets are balanced.

Example:
Input: '(()()'
Output: 1
Explanation:

The fixed string could either be ()() by deleting the first bracket, or (()()) by adding a bracket. 
These are not the only ways of fixing the string, there are many other ways by adding it in 
different positions!
*/

/* APPROACH 1: Stack. O(N) space and time */
int minChangesToFixBrackets(string str) {
    stack<char> stck;
    int count = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(') stck.push('(');
        else if (str[i] == ')') {
            if (stck.empty()) count++;
            else stck.pop();
        }
        else {
            std::cout << "INVALID INPUT\n";
            return -1;
        }
    }
    return count + stck.size();
}

/* APPROACH 2: Keep track of balance of '(' and ')' at each point. Pretty much same as stack. 
O(N) time */
int minChangesToFixBrackets2(string str) {
    int balance = 0;
    int count = 0;
    for (int i = 0; i < str.length(); i++) {
        if (str[i] == '(') balance++;
        else if (str[i] == ')') {
            balance--;
            // If there is extra ')', need to add '(' in front somewhere.
            if (balance < 0) {
                count++;
                balance++;
            }
        }
    }
    // All matched except for ${balance} '('s; need to add ${balance} ')'s to match
    return count + balance;
}

int main(int argc, char **argv) {
    string str = "(()()";
    std::cout << "APPROACH 1 TESTING: " << minChangesToFixBrackets(str) << '\n';
    std::cout << "APPROACH 2 TESTING: " << minChangesToFixBrackets2(str) << '\n';
    return 0;
}
