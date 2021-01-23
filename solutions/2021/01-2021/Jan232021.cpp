#include <iostream>
#include <vector>
using namespace std;

/*
Given a list of strings, find the list of characters that appear in all strings.
*/

/* QUESTION: only lower-case alpha chars? Will assume yes for simplicity */
#define MAX_CHARS 26

void print(vector<char> arr) {
    int n = arr.size();
    if (n == 0) {
        cout << "[]\n";
        return;
    }
    cout << "[";
    for (int i = 0; i < n - 1; i++) {
        cout << arr[i] << ", ";
    }
    cout<< arr[n - 1] << "]\n";
}

/* APPROACH 1: For each word, for each character in that word, if that character exists
in all previous words, mark it as true. Else remove it from the existsInAllWords table.
O(total chars) */
vector<char> findCommonChars(vector<string> words) {
    vector<bool> existsInAllWords(MAX_CHARS, true);
    for (int i = 0; i < words.size(); i++) {
        vector<bool> charsToKeep(MAX_CHARS, false);
        for (int j = 0; j < (int) words[i].length(); j++) {
            if (existsInAllWords[words[i][j] - 'a']) charsToKeep[words[i][j] - 'a'] = true;
        }
        for (int c = 0; c < MAX_CHARS; c++) {
            existsInAllWords[c] = charsToKeep[c];
        }
    }
    vector<char> ans;
    for (int c = 0; c < MAX_CHARS; c++) {
        if (existsInAllWords[c]) ans.push_back((char) (c + 'a'));
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<string> words = {"google", "facebook", "youtube"};
    print(findCommonChars(words));
    return 0;
}
