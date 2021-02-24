#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
Implement auto-completion. Given a large set of words (for instance 1,000,000 words) and
then a single word prefix, find all words that it can complete to.
*/

/*
QUESTION: only lowercase alpha chars? Will assume yes
*/

#define ALPHA_SIZE 26

struct TrieNode {
    TrieNode **children;
    string word;
    TrieNode() {
        children = (TrieNode **) malloc(ALPHA_SIZE * sizeof(TrieNode *));
        for (int i = 0; i < ALPHA_SIZE; i++) {
            children[i] = nullptr;
        }
        word = "";
    }
    void getAllWords(vector<string> &words) {
        if (word != "") words.push_back(word);
        for (int i = 0; i < ALPHA_SIZE; i++) {
            if (children[i] != nullptr) children[i]->getAllWords(words);
        }
    } 
};

class Trie {
    TrieNode *trie;
public:
    Trie() {
        trie = new TrieNode();
    }
    void insert(string word) {
        TrieNode *cur = trie;
        for (int i = 0; i < word.length(); i++) {
            int c = word.at(i) - 'a';
            if (cur->children[c] == nullptr) cur->children[c] = new TrieNode();
            cur = cur->children[c];
        }
        cur->word = word;
    }
    vector<string> searchPrefix(string word) {
        TrieNode *cur = trie;
        for (int i = 0; i < word.length(); i++) {
            int c = word.at(i) - 'a';
            if (cur->children[c] == nullptr) return {};
            cur = cur->children[c];
        }
        vector<string> ans;
        cur->getAllWords(ans);
        return ans;
    }
};

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

/* APPROACH 1: Trie. */
vector<string> autocomplete(vector<string> dict, string partialWord) {
    Trie *trie = new Trie();
    for (int i = 0; i < dict.size(); i++) {
        trie->insert(dict[i]);
    }
    return trie->searchPrefix(partialWord);
}

int main(int argc, char **argv) {
    vector<string> dict = {"dog", "dark", "cat", "door", "dodge"};
    string partialWord = "do";

    print(autocomplete(dict, partialWord));
    return 0;
}
