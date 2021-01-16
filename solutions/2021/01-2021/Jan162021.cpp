#include <iostream>
#include <string>
using namespace std;

/*
Given a string, determine if you can remove any character to create a palindrome.

ex.
"abcdcbea" => true (remove e)
*/

/* APPROACH 1: Test if palindromic by moving two l/r pointers from ends of string until mismatch. Then
test within mismatch is palindromic. O(N) */
bool isPalindrome(string str, int l, int r) {
    int l2 = l, r2 = r;
    while (l2 < r2) {
        if (str[l2] != str[r2]) return false;
        l2++;
        r2--;
    }
    return true;
}
bool isOneFromPalindrome(string str) {
    int l = 0, r = str.length() - 1;
    while (l < r) {
        if (str[l] == str[r]) {
            l++;
            r--;
        } else {
            if (isPalindrome(str, l+1, r) || isPalindrome(str, l, r-1)) return true;
            return false;
        }
    }
    return true;
}

int main(int argc, char **argv) {
    string test = "aebdcdedcbea";
    std::cout << isOneFromPalindrome(test) << '\n';
    return 0;
}
