#include <iostream>
#include <string>
using namespace std;

/*
Given a string that may represent a number, determine if it is a number. Here's some of examples of how the number
may be presented:

"123" # Integer
"12.3" # Floating point
"-123" # Negative numbers
"-.3" # Negative floating point
"1.5e5" # Scientific notation

Here's some examples of what isn't a proper number:
"12a" # No letters
"1 2" # No space between numbers
"1e1.2" # Exponent can only be an integer (positive or negative or 0)

Scientific notation requires the first number to be less than 10, however to simplify the solution assume the
first number can be greater than 10.
*/

/* QUESTIONS: leading/trailing spaces? Will assume no and only handle examples given. */

bool isDigit(char c) {
    return c >= '0' && c <= '9';
}

/* APPROACH 1: Single pass, tracking states. Some rules:
-only valid characters are "[0-9].e"
-only one decimal and one exp allowed
-decimal must follow an int and must be followed by an int
-e must be followed by an int
O(N) */
#define INT_STATE 0
#define FLOAT_STATE 1
#define EXP_STATE 2

bool isNumber(string s) {
    int n = s.length();
    if (n == 0) return false;
    // Handle negatives
    int i = s[0] == '-' ? 1 : 0;
    // Kick off INT_STATE
    if (i >= n || !isDigit(s[i])) return false;
    int state = INT_STATE;
    while (i < n) {
        if (isDigit(s[i])) { // Continue current state if digit
        } else if (s[i] == '.') { // Transition to FLOAT_STATE
            if (state != INT_STATE) return false;
            // Ensure following character is digit
            if (i+1 < n && !isDigit(s[i+1])) return false;
            state = FLOAT_STATE;
        } else if (s[i] == 'e' || s[i] == 'E') { // Transition to EXP_STATE
            if (state == EXP_STATE || i+1 >= n) return false;
            state = EXP_STATE;
        } else return false; // No other characters allowed
        i++;
    }
    return true;
}

int main(int argc, char **argv) {
    string s = "-53.5e91";
    std::cout << isNumber(s) << '\n';
    return 0;
}
