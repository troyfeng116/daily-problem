#include <iostream>
#include <string>
using namespace std;

/*
Given two strings, find if there is a one-to-one mapping of characters between the two strings.

Example
Input: abc, def
Output: True # a -> d, b -> e, c -> f

Input: aab, def
Ouput: False # a can't map to d and e 
*/

/* QUESTION: Only lowercase? Will assume no for simplicity */

/* APPROACH 1: Hash occurrences of each letter, and check if both directions are injective. O(N) */
bool isCharBijection(string s1, string s2) {
    int n = s1.length();
    if (s2.length() != n) return false;
    char *table1 = new char[256];
    for (int i = 0; i < 256; i++) table1[i] = 0;
    for (int i = 0; i < n; i++) {
        if (table1[(int) s1[i]] == 0) table1[(int) s1[i]] = s2[i];
        else if (table1[(int) s1[i]] != s2[i]) return false;
    }
    char *table2 = new char[256];
    for (int i = 0; i < 256; i++) table2[i] = 0;
    for (int i = 0; i < n; i++) {
        if (table2[(int) s2[i]] == 0) table2[(int) s2[i]] = s1[i];
        else if (table2[(int) s2[i]] != s1[i]) return false;
    }
    return true;
}

/* APPROACH 2: (Kind of) no map. O(N) */
bool isValid(string s1, int *count1, string s2) {
    int *count2 = new int[256];
    for (int i = 0; i < 256; i++) count2[i] = -1;
    for (int i = 0; i < s1.length(); i++) {
        int c1 = (int) s1[i], c2 = (int) s2[i];
        int index = count1[c1];
        if (i == index) {
            if (count2[c2] != -1) return false;
            count2[c2] = index;
        }
        else if (s2[i] != s2[index]) return false;
    }
    return true;
}
bool isCharBijection2(string s1, string s2) {
    int n = s1.length();
    if (s2.length() != n) return false;
    // Store first occurrence of each letter in s1 in count1.
    int *count1 = new int[256];
    for (int i = 0; i < 256; i++) count1[i] = -1;
    for (int i = 0; i < n; i++) {
        int c = (int) s1[i];
        if (count1[c] == -1) count1[c] = i;
    }
    return isValid(s1, count1, s2);
}

int main(int argc, char **argv) {
    string s1 = "abc";
    string s2 = "def";
    string s3 = "aab";
    string s4 = "def";
    std::cout << "APPROACH 1 TESTNG: " << isCharBijection(s1, s2) << " " << isCharBijection(s3, s4) << '\n';
    std::cout << "APPROACH 2 TESTNG: " << isCharBijection2(s1, s2) << " " << isCharBijection2(s3, s4) << '\n';
    return 0;
}