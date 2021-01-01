#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
Given a list of words, and an arbitrary alphabetical order, verify that the words are in order of 
the alphabetical order.

Example:
Input:
words = ["abcd", "efgh"], order="zyxwvutsrqponmlkjihgfedcba"

Output: False
Explanation: 'e' comes before 'a' so 'efgh' should come before 'abcd'

Example 2:
Input:
words = ["zyx", "zyxw", "zyxwy"],
order="zyxwvutsrqponmlkjihgfedcba"

Output: True
Explanation: The words are in increasing alphabetical order
*/

/* APPROACH 1: Hash all 26 letters to their position in the new alphabetical order, and compare
each adjacent word by that order. Return 1 if a>b, -1 if a<b, and 0 if a=b like compareTo.
Runs in O(lengths of words) */
int compare(string a, string b, int newPos[]) {
    for (int i = 0; i < a.length(); i++) {
        if (i >= b.length()) return 1;
        if (newPos[a.at(i)-'a'] < newPos[b.at(i)-'a']) return -1;
        else if (newPos[a.at(i)-'a'] > newPos[b.at(i)-'a']) return 1;
    }
    return a.length() < b.length() ? -1 : 0;
}
bool isNewAlphaOrder(vector<string> words, string newOrder) {
    int newPos[26];
    for (int i = 0; i < newOrder.length(); i++) {
        newPos[newOrder.at(i)-'a'] = i;
    }
    for (int i = 0; i < words.size()-1; i++) {
        if (compare(words[i], words[i+1], newPos) > 0) return false;
    }
    return true;
}

int main(int argc, char **argv) {
    vector<string> words;
    words.push_back("zx");
    words.push_back("zyxw");
    words.push_back("zyxwy");
    string order = "zyxwvutsrqponmlkjihgfedcba";
    std::cout << isNewAlphaOrder(words, order) << '\n';
    return 0;
}
