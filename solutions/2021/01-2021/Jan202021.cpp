#include <iostream>
using namespace std;

/*
Given a non-negative integer n, convert the integer to hexadecimal and return the result as a string.
Hexadecimal is a base 16 representation of a number, where the digits are 0123456789ABCDEF. Do not
use any builtin base conversion functions like hex.

ex. 123 => "7B"
*/

#define HEX_DIGITS "0123456789ABCDEF"

/* APPROACH 1: Simple base conversion. Strip away last digits. */
string decToHex(int n) {
    string ans = "";
    while (n != 0) {
        ans = HEX_DIGITS[n % 16] + ans;
        n /= 16;
    }
    return ans;
}

int main(int argc, char **argv) {
    int n = 123;
    std::cout << decToHex(n) << '\n';
    return 0;
}
