#include <iostream>
#include <string>
using namespace std;

/*

Given a string, return the first recurring letter that appears. If there are no recurring letters, return None.

Example:
Input: qwertty
Output: t

Input: qwerty
Output: None
*/

#define SIZE 256

/* APPROACH 1: Hashmap. O(N) */
char firstRepeatChar(string word) {
    bool found[SIZE];
    for (int i = 0; i < SIZE; i++) found[i] = false;
    for (int i = 0; i < word.length(); i++) {
        if (found[(int) word[i]]) return word[i];
        found[(int) word[i]] = true;
    }
    std::cout << "No recurring letters in " << word << '\n';
    return '#';
}

int main(int argc, char **argv) {
    string w1 = "qwertty";
    string w2 = "qwerty";
    std::cout << firstRepeatChar(w1) << '\n';
    std::cout << firstRepeatChar(w2) << '\n';
    return 0;
}
