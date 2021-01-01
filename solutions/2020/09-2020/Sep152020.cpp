#include <iostream>
#include <string>
using namespace std;

/*
You are given a string s, and an integer k. Return the length of the longest 
substring in s that contains at most k distinct characters.

For instance, given the string:
aabcdefff and k = 3, then the longest substring with 3 distinct characters 
would be defff. The answer should be 5.
*/

/* QUESTION: only lowercase alphabetic chars? Will assume yes */
#define NUM_CHARS 26

/* APPROACH 1: Sliding window. Set l=0 and slide r until we hit k+1 distinct
characters. Keep a count of the number of each character, and slide l until we
get to <= k distinct characters. l and r visit each character at most once, and 
only 26 letters to store and check: O(N) time and constant space. */
bool atMostKDistinct(int *counts, int k) {
    int distinct = 0;
    for (int i = 0; i < NUM_CHARS; i++) {
        if (counts[i] > 0) distinct++;
    }
    return distinct <= k;
}
string longestKDistinctSubstr(string s, int k) {
    int maxL = 0;
    int maxR = 0;
    int count[NUM_CHARS];
    for (int i = 0; i < NUM_CHARS; i++) count[i] = 0;
    int l = 0;
    int r = 0;
    for (int i = 0; i < s.length(); i++) {
        count[s.at(i)-'a']++;
        r++;
        while (!atMostKDistinct(count, k)) {
            count[s.at(l)-'a']--;
            l++;
        }
        if (r-l+1 > maxR-maxL+1) {
            maxL = l;
            maxR = r;
        }
    }
    return s.substr(maxL, maxR-maxL+1);
}

int main(int argc, char **argv) {
    string test = "aabcaadefff";
    int k = 4;
    std::cout << longestKDistinctSubstr(test, k) << '\n';
    return 0;
}
