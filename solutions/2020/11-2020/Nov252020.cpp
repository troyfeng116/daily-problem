#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
A UTF-8 character encoding is a variable width character encoding that can vary from 1 to 4 bytes depending on 
the character. The structure of the encoding is as follows:
1 byte:  0xxxxxxx
2 bytes: 110xxxxx 10xxxxxx
3 bytes: 1110xxxx 10xxxxxx 10xxxxxx
4 bytes: 11110xxx 10xxxxxx 10xxxxxx 10xxxxxx
For more information, you can read up on the Wikipedia Page.

Given a list of integers where each integer represents 1 byte, return whether or not the list of integers is 
a valid UTF-8 encoding.

ex.
[197, 130, 1] => [11000101 10000010 00000001], matches 2-byte + 1-byte pattern. -> true
[235, 140, 4] => [11101011 10001100 00000100], we expect 3-byte pattern but last doesn't match. -> false
*/

/*
QUESTIONS:
This is pretty confusing. So first byte tells us how many bytes total, and then the rest follow the pattern?
What is the length of the list? Can there be more than 1 UTF-8 character? Will assume yes and process in 
order.
What if number is greater than 2^8 - 1? Will assume we take 8 least significant bits (per Wikipedia).
*/

/* APPROACH 1: process ints in list one by one to 1-byte representations and check rules. O(N) time + space */
string getByte(int n) {
    string ans = "";
    for (int i = 0; i < 8; i++) {
        ans = to_string(n%2) + ans;
        n /= 2;
    }
    return ans;
}
bool checkValidUTF8(vector<int> list) {
    int numBytesLeftInThisChar = 0;
    for (int i = 0; i < list.size(); i++) {
        string s = getByte(list[i]);
        // If new char incoming, process this byte to see how many bytes are in the new char.
        if (numBytesLeftInThisChar == 0) {
            for (int j = 0; j < 8; j++) {
                if (s[j] == '0') break;
                numBytesLeftInThisChar++;
            }
            if (numBytesLeftInThisChar == 0) continue;
            if (numBytesLeftInThisChar == 1 || numBytesLeftInThisChar > 4) return false;
        }
        // Else, we are currently in a UTF-8 char, and it needs to look like 10xxxxxx.
        else {
            if (s[0] != '1' || s[1] != '0') return false;
        }
        numBytesLeftInThisChar--;
    }
    // Handle case of incomplete UTF-8 char at end of list.
    return numBytesLeftInThisChar == 0;
}

/* APPROACH 2: same as approach 1 but use bit manipulation instead of strings. O(N) */
bool checkValidUTF8_2(vector<int> list) {
    int numBytesLeftInThisChar = 0;
    int mask1 = 1 << 7;
    int mask2 = 1 << 6;
    for (int i = 0; i < list.size(); i++) {
        // If new char incoming, process this byte to see how many bytes are in the new char.
        if (numBytesLeftInThisChar == 0) {
            int mask = 1 << 7;
            while ((list[i] & mask) != 0) {
                mask = mask >> 1;
                numBytesLeftInThisChar++;
            }
            if (numBytesLeftInThisChar == 0) continue;
            if (numBytesLeftInThisChar == 1 || numBytesLeftInThisChar > 4) return false;
        }
        // Else, we are currently in a UTF-8 char, and it needs to look like 10xxxxxx.
        else {
            if ((list[i] & mask1) == 0 || (list[i] & mask2) != 0) return false;
        }
        numBytesLeftInThisChar--;
    }
    // Handle case of incomplete UTF-8 char at end of list.
    return numBytesLeftInThisChar == 0;
}

int main(int argc, char **argv) {
    vector<int> list = {197, 130, 1};
    std::cout << "APPROACH 1 TESTING: " << checkValidUTF8(list) << '\n';
    std::cout << "APPROACH 2 TESTING: " << checkValidUTF8_2(list) << '\n';
    return 0;
}
