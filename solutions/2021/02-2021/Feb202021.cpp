#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
Find all words that are concatenations of other words in a list.

ex.
["um", "brella", "umbrella", "cat", "cats", "dog", "catsdog"] -> ["umbrella", "catsdog"]
*/

void print(vector<string> arr) {
    if (arr.size() == 0) {
        cout << "[]\n";
        return;
    }
    cout << "[";
    for (int i = 0; i < arr.size() - 1; i++) {
        cout << arr[i] << ", ";
    }
    cout << arr.back() << "]\n";
}

struct TrieNode {
    TrieNode **children;
    bool isEOW;
    TrieNode() {
        children = (TrieNode**) malloc(26 * (sizeof (TrieNode*)));
        for (int i = 0; i < 26; i++) children[i] = nullptr;
        isEOW = false;
    }
};

class Trie {
    TrieNode *root;
public:
    Trie() {
        root = new TrieNode();
    }
    void insert(string word) {
        TrieNode *cur = root;
        for (int i = 0; i < word.length(); i++) {
            int c = word.at(i) - 'a';
            if (cur->children[c] == nullptr) cur->children[c] = new TrieNode();
            cur = cur->children[c];
        }
        cur->isEOW = true;
    }
    bool dfs(string &word, int start, vector<int> &dp, int count) {
        if (start >= word.length()) return count >= 2;
        if (dp[start] != -1) return dp[start] == 1;
        TrieNode *cur = root;
        for (int i = start; i < word.length(); i++) {
            int c = word.at(i) - 'a';
            if (cur->children[c] == nullptr) {
                dp[start] = 0;
                return false;
            }
            cur = cur->children[c];
            if (cur->isEOW && dfs(word, i + 1, dp, count + 1)) {
                dp[start] = 1;
                return true;
            }
        }
        dp[start] = 0;
        return false;
    }
};

/* APPROACH 1: Trie + dynamic programming. */
vector<string> findAllConcatenatedWords(vector<string> words) {
    Trie trie;
    for (int i = 0; i < words.size(); i++) {
        trie.insert(words[i]);
    }
    vector<string> ans;
    for (int i = 0; i < words.size(); i++) {
        vector<int> dp(words[i].length(), -1);
        if (trie.dfs(words[i], 0, dp, 0)) ans.push_back(words[i]);
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<string> test = {"um", "brella", "umbrella", "cat", "cats", "dog", "catsdog"};
    print(findAllConcatenatedWords(test));
    return 0;
}
