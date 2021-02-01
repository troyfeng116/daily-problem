#include <iostream>
using namespace std;

/*
Given an integer, reverse the digits. Do not convert the integer into a string and reverse it.
*/

/*
QUESTION: Handle integer overflow? Will assume no for simplicity
*/

/* APPROACH 1: Extract last digit and construct reversed integer digit by digit. O(#digits) = O(log(n)) */
int reverseDigits(int n) {
    int ans = 0;
    bool neg = n < 0;
    n = abs(n);
    while (n > 0) {
        ans = ans * 10 + n % 10;
        n /= 10;
    }
    return neg ? -ans : ans;
}

int main(int argc, char **argv) {
    cout << reverseDigits(-135) << '\n';
    return 0;
}
