#include <iostream>
#include <string>
using namespace std;

/*
Given an integer, convert the integer to a roman numeral. You can assume the input will be between 1 to 3999.

The rules for roman numerals are as following:

There are 7 symbols, which correspond to the following values.
I   1
V   5
X   10
L   50
C   100
D   500
M   1000
The value of a roman numeral are the digits added together. For example the roman numeral 'XX' is
X + X = 10 + 10 = 20. Typically the digits are listed from largest to smallest, so X should always come
before I. Thus the largest possible digits should be used first before the smaller digits (so to
represent 50, instead of XXXXX, we should use L).

There are a couple special exceptions to the above rule.

To represent 4, we should use IV instead of IIII. Notice that I comes before V.
To represent 9, we should use IX instead of VIIII.
To represent 40, we should use XL instead of XXXX.
To represent 90, we should use XC instead of LXXXX.
To represent 400, we should use CD instead of CCCC.
To represent 900, we should use CM instead of DCCCC.
*/

/* APPROACH 1: "peel" away each roman letter. */
string intToRoman(int n) {
    string ans = "";
    int chunks[] = {1000, 900, 500, 400, 100, 90, 50, 40, 10, 9, 5, 4, 1};
    string romanLetters[] = {"M", "CM", "D", "CD", "C", "XC", "L", "XL", "X", "IX", "V", "IV", "I"};
    for (int i = 0; i < 13; i++) {
        while (n >= chunks[i]) {
            n -= chunks[i];
            ans += romanLetters[i];
        }
    }
    return ans;
}

/* APPROACH 2: Guaranteed at most 4 digits. Extract each digit and hash to corresponding Roman
letter chunk. */
string intToRoman2(int n) {
    string m[] = {"", "M", "MM", "MMM"};
    string c[] = {"", "C", "CC", "CCC", "CD", "D", "DC", "DCC", "DCCC", "CM"};
    string x[] = {"", "X", "XX", "XXX", "XL", "L", "LX", "LXX", "LXXX", "XC"};
    string i[] = {"", "I", "II", "III", "IV", "V", "VI", "VII", "VIII", "IX"};

    string thousands = m[n / 1000];
    string hundereds = c[(n % 1000) / 100];
    string tens =  x[(n % 100) / 10];
    string ones = i[n % 10];

    return thousands + hundereds + tens + ones;
}

int main(int argc, char **argv) {
    int n = 444;
    cout << "APPROACH 1 TESTING: " << intToRoman(n) << '\n';
    cout << "APPROACH 2 TESTING: " << intToRoman2(n) << '\n';
    return 0;
}
