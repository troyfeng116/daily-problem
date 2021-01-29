#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
Given a string s and a character c, find the distance for all characters in the string to the character
c in the string s. You can assume that the character c will appear at least once in the string.

ex. word = 'helloworld', char = 'l' => [2, 1, 0, 0, 1, 2, 2, 1, 0, 1]
*/

void print(vector<int> arr) {
    if (arr.size() == 0) {
        cout << "[]\n";
        return;
    }
    cout << "[";
    for (int i = 0; i < arr.size() - 1; i++) {
        cout << arr[i] << ", ";
    }
    cout << arr[arr.size() - 1] << "]\n";
}

/* APPROACH 1: Brute force. Calculate distance from index to l using two pointers. O(N^2) */
int closestIndex(string word, int i, char c) {
    for (int dist = 0; dist < word.size(); dist++) {
        if (i + dist < word.length() && word[i + dist] == c) return dist;
        if (i - dist >= 0 && word[i - dist] == c) return dist;
    }
    return -1;
}
vector<int> closestToChar(string word, char c) {
    int n = word.length();
    vector<int> ans(n, 0);
    for (int i = 0; i < n; i++) {
        ans[i] = closestIndex(word, i, c);
    }
    return ans;
}

/* APPROACH 2: Extra space. Store closest occurrence to the right and left of each index in two
arrays. One traversal to retrieve answer. O(N) time + space */
vector<int> closestToChar2(string word, char c) {
    int n = word.length();
    vector<int> closestToLeft(n, INT_MAX), closestToRight(n, INT_MAX);
    for (int i = 0; i < n; i++) {
        if (word[i] == c) closestToLeft[i] = 0;
        else if (i != 0 && closestToLeft[i - 1] != INT_MAX) closestToLeft[i] = closestToLeft[i - 1] + 1;
        if (word[n - i - 1] == c) closestToRight[n - i - 1] = 0;
        else if (i != 0 && closestToRight[n - i] != INT_MAX) closestToRight[n - i - 1] = closestToRight[n - i] + 1;
    }
    vector<int> ans(n, 0);
    for (int i = 0; i < n; i++) {
        ans[i] = min(closestToLeft[i], closestToRight[i]);
    }
    return ans;
}

int main(int argc, char **argv) {
    string word = "helloworld";
    char c = 'l';

    std::cout << "APPROACH 1 TESTING: ";
    print(closestToChar(word, c));

    std::cout << "APPROACH 2 TESTING: ";
    print(closestToChar2(word, c));
    return 0;
}
