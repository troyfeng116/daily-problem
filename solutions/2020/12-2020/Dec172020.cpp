#include <iostream>
#include <vector>
#include <string>
#include <unordered_set>
using namespace std;

/*
Given a phone number, return all valid words that can be created using that phone number.

For instance, given the phone number 364 and dictionary ['dog', 'fish', 'cat', 'fog'],
we can construct the words ['dog', 'fog'].
*/

/* QUESTION: what does the keypad look like lol. */

vector<char> *createTable() {
    vector<char> *table = (vector<char>*) malloc(10 * sizeof(vector<char>));
    for (int i = 2; i <= 6; i++) {
        char c = (char) ((i - 2) * 3 + 'a');
        vector<char> list = {c, (char) (c+1), (char) (c+2)};
        table[i] = list;
    }
    table[7] = {'p', 'q', 'r', 's'};
    table[8] = {'t', 'u', 'v'};
    table[9] = {'w', 'x', 'y', 'z'};
    return table;
}

const vector<char> *table = createTable();

void print(vector<string> arr) {
    if (arr.size() == 0) {
        std::cout << "[]\n";
        return;
    }
    std::cout << '[';
    for (int i = 0; i < arr.size() - 1; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[arr.size()-1] << "]\n";
}

/* APPROACH 1: DFS with set. Max O(4^N) ish */
void dfs(string number, string cur, int i, unordered_set<string> set, vector<string> &ans) {
    if (i >= number.length()) {
        if (set.count(cur) > 0) ans.push_back(cur);
        return;
    }
    vector<char> list = table[number[i] - '0'];
    for (char c : list) {
        dfs(number, cur + c, i + 1, set, ans);
    }
}
vector<string> findAllValidWords(string number, vector<string> dict) {
    vector<string> res;
    unordered_set<string> set;
    for (string w: dict) set.insert(w);
    dfs(number, "", 0, set, res);
    return res;
}

/* APPROACH 2: DFS, walking through Trie instead of set to terminate recursion at non-matching
prefix. Still O(4^N) ish */
struct TrieNode {
    string word;
    TrieNode *children[26];
    TrieNode() {
        word = "";
        for (int i = 0; i < 26; i++) {
            children[i] = nullptr;
        }
    }
};
void insert(TrieNode *dict, string word) {
    TrieNode *cur = dict;
    for (int i = 0; i < word.length(); i++) {
        int c = word[i] - 'a';
        if (cur->children[c] == NULL) {
            cur->children[c] = new TrieNode();
        }
        cur = cur->children[c];
    }
    cur->word = word;
}
void dfs2(string number, int i, TrieNode *cur, vector<string> &ans) {
    if (i >= number.length()) {
        if (cur->word.length() > 0) ans.push_back(cur->word);
        return;
    }
    vector<char> list = table[number[i] - '0'];
    for (char ch : list) {
        int c = ch - 'a';
        if (cur->children[c] != NULL) {
            dfs2(number, i+1, cur->children[c], ans);
        }
    }
}
vector<string> findAllValidWords2(string number, vector<string> dict) {
    vector<string> res;
    TrieNode *trie = new TrieNode();
    for (string w : dict) insert(trie, w);
    dfs2(number, 0, trie, res);
    return res;
}

int main(int argc, char **argv) {
    vector<string> dict = {"dog", "fish", "cat", "fog"};
    string number = "364";
    
    vector<string> res1 = findAllValidWords(number, dict);
    std::cout << "APPROACH 1 TESTING: ";
    print(res1);

    vector<string> res2 = findAllValidWords2(number, dict);
    std::cout << "APPROACH 2 TESTING: ";
    print(res2);
    return 0;
}
