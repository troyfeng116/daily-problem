#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
Given 2 strings s and t, find and return all indexes in string s where t is an anagram.

ex.
s = 'acdbacdacb', t = 'abc' => [3, 7]
*/

/* QUESTION: only lowercase alphabetic chars? Will assume yes */
#define ALPHA_SIZE 26

void print(vector<int> arr) {
    if (arr.size() == 0) {
        std::cout << "[]\n";
        return;
    }
    std::cout << "[";
    for (int i = 0; i < arr.size() - 1; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[arr.size() - 1] << "]\n";
}

/* APPROACH 1: Brute force. For each t-length substr of s, check if anagrams.
O(len(s) * len(t)) */
bool isAnagram(string a, string b) {
    int map[ALPHA_SIZE];
    for (int i = 0; i < ALPHA_SIZE; i++) map[i] = 0;
    for (int i = 0; i < a.length(); i++) {
        map[a[i] - 'a']++;
        map[b[i] - 'a']--;
    }
    for (int i = 0; i < ALPHA_SIZE; i++) {
        if (map[i] != 0) return false;
    }
    return true;
}
vector<int> findAnagrams(string s, string t) {
    int len_s = s.length(), len_t = t.length();
    vector<int> ans;
    if (len_s < len_t) return ans;
    for (int i = 0; i <= len_s - len_t; i++) {
        string sub_s = s.substr(i, len_t);
        if (isAnagram(t, sub_s)) ans.push_back(i);
    }
    return ans;
}

/* APPROACH 2: Sliding window, keep map of letter counts to find anagrams. O(N) assuming
constant size alphabet */
bool isEqual(int *map1, int *map2) {
    for (int i = 0; i < ALPHA_SIZE; i++) {
        if (map1[i] != map2[i]) return false;
    }
    return true;
}
vector<int> findAnagrams2(string s, string t) {
    int len_s = s.length(), len_t = t.length();
    vector<int> ans;
    if (len_s < len_t) return ans;
    int map_s[ALPHA_SIZE], map_t[ALPHA_SIZE];
    for (int i = 0; i < ALPHA_SIZE; i++) {
        map_s[i] = 0;
        map_t[i] = 0;
    }
    for (int i = 0; i < len_t; i++) {
        map_s[s[i] - 'a']++;
        map_t[t[i] - 'a']++;
    }
    int l = 0, r = len_t - 1;
    while (r < len_s) {
        if (isEqual(map_s, map_t)) ans.push_back(l);
        map_s[s[l] - 'a']--;
        l++;
        r++;
        if (r < len_s) map_s[s[r] - 'a']++;
    }
    return ans;
}

int main(int argc, char **argv) {
    string s = "acdbacdacb", t = "abc";

    std::cout << "APPROACH 1 TESTING: ";
    print(findAnagrams(s, t));

    std::cout << "APPROACH 2 TESTING: ";
    print(findAnagrams2(s, t));
    return 0;
}
