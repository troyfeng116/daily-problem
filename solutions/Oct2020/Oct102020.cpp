#include <iostream>
#include <string>
using namespace std;

/*
Given a string with a certain rule: k[string] should be expanded to string k times. So for example, 
3[abc] should be expanded to abcabcabc. Nested expansions can happen, so 2[a2[b]c] should be expanded 
to abbcabbc.
*/

/* QUESTIONS:
-Are the strings only lower-case alpha? Or are there numbers too? No escaped chars or
special characters (like square brackets)? Will assume only a-z.
-Is k single digit? Will assume no
-Valid brackets? Will assume yes
*/

/* APPROACH 1: Should take one pass. Recursion with a pass-by-reference index. O(N) */
// Given that str[l] is a digit, find integer representation of that sequence of digits.
// Returns int, sets l to index of left bracket.
int findK(string str, int &l) {
    int ans = str.at(l)-'0';
    char c;
    l++;
    while ((c = str.at(l))-'0' >= 0 && c-'0' <= 9) {
        ans *= 10;
        ans += (c-'0');
        l++;
    }
    return ans;
}
// Find string inside brackets (recursively). Starts with l at left bracket, ends with l at right bracket.
string decodeAux(string str, int &l) {
    std::cout << "DECODEAUX " << l << '\n';
    if (str.at(l) != '[') {
        std::cout << "ERROR AT DECODEAUX\n";
        return "ERROR";
    }
    string ans = "";
    l++;
    while (l < str.length()) {
        char c = str.at(l);
        if (c == ']') return ans;
        if (c-'0' >= 0 && c-'0' <= 9) {
            int repeat = findK(str, l);
            string chunk = decodeAux(str, l);
            for (int i = 0; i < repeat; i++) ans += chunk;
            l++;
        }
        else {
            ans += c;
            l++;
        }
    }
    return ans;
}
string decode(string str) {
    string ans = "";
    int i = 0;
    while (i < str.length()) {
        char c = str.at(i);
        if (c-'0' >= 0 && c-'0' <= 9) {
            int repeat = findK(str, i);
            string chunk = decodeAux(str, i);
            for (int j = 0; j < repeat; j++) ans += chunk;
        }
        else {
            ans += c;
        }
        i++;
    }
    return ans;
}

int main(int argc, char **argv) {
    string test = "2[a2[b]c]";
    string res = decode(test);
    std::cout << res << '\n';
    return 0;
}
