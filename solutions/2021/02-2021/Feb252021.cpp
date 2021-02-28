#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
using namespace std;

/*
A criminal is constructing a ransom note. In order to disguise his handwriting, he is cutting
out letters from a magazine.

Given a magazine of letters and the note he wants to write, determine whether he can
construct the word.

ex.
magazine = ['a', 'b', 'c', 'd', 'e', 'f'], word = 'bed' -> true
magazine = ['a', 'b', 'c', 'd', 'e', 'f'], word = 'cat' -> false
*/

/* APPROACH 1: hashmap for characters to counts. O(N) time, O(alphabet) space ~ constant */
bool canMakeRansomNote(vector<char> letters, string message) {
    unordered_map<char, int> map;
    for (int i = 0; i < letters.size(); i++) {
        if (map.find(letters[i]) == map.end()) {
            map[letters[i]] = 0;
        }
        map[letters[i]]++;
    }
    for (int i = 0; i < message.length(); i++) {
        char c = message.at(i);
        if (map.find(c) == map.end()) return false;
        if (map[c] <= 0) return false;
        map[c]--;
    }
    return true;
}

int main(int argc, char **argv) {
    vector<char> magazine = {'a', 'b', 'c', 'd', 'e', 'f'};
    string msg1 = "bed";
    string msg2 = "cat";
    cout << canMakeRansomNote(magazine, msg1) << ' ' << canMakeRansomNote(magazine, msg2) << '\n';
    return 0;
}
