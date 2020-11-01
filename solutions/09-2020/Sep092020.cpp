#include <iostream>
#include <string>
using namespace std;

/*
Given two strings A and B of lowercase letters, return true if and only if we can swap 
two letters in A so that the result equals B.

Example 1:
Input: A = "ab", B = "ba"
Output: true
Example 2:
Input: A = "ab", B = "ab"
Output: false
Example 3:
Input: A = "aa", B = "aa"
Output: true
Example 4:
Input: A = "aaaaaaabc", B = "aaaaaaacb"
Output: true
Example 5:
Input: A = "", B = "aa"
Output: false
*/

/* QUESTIONS: only lowercase? Will assume yes */

/* APPROACH 1: Walk through the two strings. Once two characters don't match, store
them. If two more characters don't match, they have to be the same as the first two
mismatches but in the other string. Keep going: if there aren't exactly two or zero
mismatches by the end, return false. */
bool areBuddies(string A, string B) {
    if (A.length() != B.length()) return false;
    char c1 = '\0';
    char c2 = '\0';
    int mismatches = 0;
    int count[26];
    for (int i = 0; i < 26; i++) count[i]=0;
    for (int i = 0; i < A.length(); i++) {
        count[A.at(i)-97]++;
        if (A.at(i) != B.at(i)) {
            if (mismatches == 0) {
                c1 = A.at(i);
                c2 = B.at(i);
                mismatches++;
            }
            else if (mismatches == 1) {
                if (A.at(i) != c2 || B.at(i) != c1) return false;
                mismatches++;
            }
            else return false;
        }
    }
    if (mismatches == 0) {
        for (int c = 0; c < 26; c++) {
            if (count[c] >= 2) return true;
        }
        return false;
    }
    return mismatches == 2;
}

int main(int argc, char **argv) {
    string test1 = "aaaaaaabc";
    string test2 = "aaaaaaacb";
    std::cout << areBuddies(test1,test2) << '\n';
    return 0;;
}
