#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
Given a list of strings, find the longest common prefix between all strings.
*/

/* APPROACH 1: sort and find LCP between first and last words. O(|M| * N * log N) */
string longestCommonPrefix(vector<string> words) {
    int n = words.size();
    if (n == 0) return "";
    if (n == 1) return words[0];
    sort(words.begin(), words.end());
    string ans = "";
    for (int i = 0; i < words[0].length() && i < words[n - 1].length(); i++) {
        if (words[0][i] == words[n - 1][i]) ans += words[0][i];
    }
    return ans;
}

/* APPROACH 2: check char by char. Move index one at a time while all words match at index.
O(N * M), N is #words and M is |longest word| */
bool lettersAtIndexAreEqual(vector<string> words, int index) {
    int n = words.size();
    if (n == 0) return false;
    if (index >= words[0].length()) return false;
    char c = words[0][index];
    for (int i = 1; i < n; i++) {
        if (index >= words[i].length()) return false;
        if (words[i][index] != c) return false;
    }
    return true;
}
string longestCommonPrefix2(vector<string> words) {
    int wordIndex = 0;
    string ans = "";
    while (lettersAtIndexAreEqual(words, wordIndex)) {
        ans += words[0][wordIndex];
        wordIndex++;
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<string> words = {"helloword", "hellokitty", "hell"};
    cout << "APPROACH 1 TESTING: " << longestCommonPrefix(words) << '\n';
    cout << "APPROACH 2 TESTING: " << longestCommonPrefix2(words) << '\n';
    return 0;
}
