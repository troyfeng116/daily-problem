#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
Given a list of words, for each word find the shortest unique prefix. You can assume a word will not be a substring of 
another word (i.e. play and playing won't be in the same words list)

Example
Input: ['joma', 'john', 'jack', 'techlead']
Output: ['jom', 'joh', 'ja', 't']
*/

#define MAX 26

struct Trie {
    string word;
    Trie *children[26];
    int count;
    Trie() {
        word = "";
        count = 0;
        for (int i = 0; i < MAX; i++) children[i] = NULL;
    }
    Trie(string w) {
        word = w;
        count = 0;
        for (int i = 0; i < MAX; i++) children[i] = NULL;
    }
};

void insert(Trie *t, string word) {
    Trie *cur = t;
    for (int i = 0; i < word.length(); i++) {
        int c = word[i] - 'a';
        if (cur->children[c] == NULL) {
            cur->children[c] = new Trie();
        }
        cur = cur->children[c];
        cur->count++;
    }
    cur->word = word;
}

void print(vector<string> words) {
    std::cout << "[";
    for (int i = 0; i < words.size()-1; i++) {
        std::cout << words[i] << ", ";
    }
    std::cout << words[words.size()-1] << "]\n";
}

/* APPROACH 1: Trie with count of number of words passing through each node.
O(26^(len longest word)) space, O(N*K) time (N = words.size, K = len each word) */
string getShortestUniquePrefix(string w, Trie *dict) {
    Trie *cur = dict;
    for (int i = 0; i < w.size(); i++) {
        int c = w[i] - 'a';
        cur = cur->children[c];
        if (cur->count == 1) return w.substr(0, i+1);
    }
    return w;
}
vector<string> shortestUniquePrefixes(vector<string> words) {
    Trie *dict = new Trie();
    for (int i = 0; i < words.size(); i++) insert(dict, words[i]);
    vector<string> ans;
    for (int i = 0; i < words.size(); i++) ans.push_back(getShortestUniquePrefix(words[i], dict));
    return ans;
}

/* APPROACH 2: Sorting. Once sorted, the shortest unique prefix of a word must be the shortest between the longest
common prefix between word and its neighbors. Does not preserve ordering. O(N*(K + log N)) */
int longestCommonPrefix(string a, string b) {
    int i = 0;
    while (i < a.length() && i < b.length() && a[i] == b[i]) i++;
    return i;
}
vector<string> shortestUniquePrefixes2(vector<string> &words) {
    sort(words.begin(), words.end());
    int n = words.size();
    vector<string> ans(n);
    int lcp = longestCommonPrefix(words[0], words[1]);
    ans[0] = words[0].substr(0, lcp+1);
    // prev_prefix = LCP between word and left neighbor.
    string prev_prefix = words[1].substr(0, lcp+1);
    for (int i = 1; i < n - 1; i++) {
        lcp = longestCommonPrefix(words[i], words[i+1]);
        ans[i] = lcp+1 > prev_prefix.length() ? words[i].substr(0, lcp+1) : prev_prefix;
        prev_prefix = words[i+1].substr(0, lcp+1);
    }
    lcp = longestCommonPrefix(words[n-2], words[n-1]);
    ans[n-1] = words[n-1].substr(0, lcp+1);
    return ans;
}

int main(int argc, char **argv) {
    vector<string> words = {"joma", "john", "jack", "techlead"};

    vector<string> res1 = shortestUniquePrefixes(words);
    std::cout << "APPROACH 1 TESTING: ";
    print(res1);

    vector<string> res2 = shortestUniquePrefixes2(words);
    std::cout << "APPROACH 2 TESTING: ";
    print(res2);
    return 0;
}
