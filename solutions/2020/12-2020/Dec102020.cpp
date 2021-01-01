#include <iostream>
#include <string>
using namespace std;

/*
Given a string, determine if there is a way to arrange the string such that the string is a palindrome. If such 
arrangement exists, return a palindrome (There could be many arrangements). Otherwise return None.
*/

#define SIZE 256

/* APPROACH 1: Hash all letter counts. There can be at most one letter with an odd count. Construct palindrome
from buckets. O(N) time + space */
string rearrangePalindrome(string word) {
    int count[SIZE];
    for (int i = 0; i < SIZE; i++) count[i] = 0;
    for (int i = 0; i < word.length(); i++) {
        count[(int) word[i]]++;
    }
    int odd = -1;
    for (int c = 0; c < SIZE; c++) {
        if (count[c] % 2 == 1) {
            if (odd >= 0) return "none";
            odd = c;
        }
    }
    string ans = "";
    if (odd >= 0) {
        while (count[odd] > 0) {
            ans += (char) odd;
            count[odd]--;
        }
    }
    for (int c = 0; c < SIZE; c++) {
        while (count[c] > 0) {
            ans = ((char) c) + ans + ((char) c);
            count[c] -= 2;
        }
    }
    return ans;
}

int main(int argc, char **argv) {
    string test = "amanaplanacanalpanama";
    std::cout << rearrangePalindrome(test) << '\n';
    return 0;
}
