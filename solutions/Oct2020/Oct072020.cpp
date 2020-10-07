#include <iostream>
using namespace std;

/*
Write a function that reverses the digits a 32-bit signed integer, x. Assume that 
the environment can only store integers within the 32-bit signed integer range, 
[-2^31, 2^31 - 1]. The function returns 0 when the reversed integer overflows.

Example:
Input: 123
Output: 321
*/

/* APPROACH 1: */
int reverseDigits(int n) {
    int ans = 0;
    bool positive = n>0;
    while (n != 0) {
        if (positive && ans > INT_MAX/10) return 0;
        if (!positive && ans < INT_MIN/10) return 0;
        ans *= 10;
        if (positive && ans > INT_MAX - (n%10)) return 0;
        if (!positive && ans < INT_MIN - (n%10)) return 0;
        ans += n%10;
        n /= 10;
    }
    return ans;
}

int main(int argc, char **argv) {
    int test = -12345;
    int res = reverseDigits(test);
    std::cout << res << '\n';
    return 0;
}
