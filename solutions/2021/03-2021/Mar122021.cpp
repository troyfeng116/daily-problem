#include <iostream>
using namespace std;

/*
Write a function that reverses the digits a 32-bit signed integer, x. Assume that the environment
can only store integers within the 32-bit signed integer range, [-2^31, 2^31 - 1]. The function
returns 0 when the reversed integer overflows.
*/

/* APPROACH 1: Peel away digits and add them in reverse order. Check if overflow. O(# digits) */
int reverseDigits(int n) {
    if (n == INT_MIN) return 0;
    bool isNegative = n < 0;
    n = abs(n);
    int ans = 0;
    while (n != 0) {
        if (ans > INT_MAX / 10) return 0;
        else if (ans * 10 > INT_MAX - n % 10) return 0;
        ans = ans * 10 + n % 10;
        n /= 10;
    }
    return isNegative ? -ans : ans;
}

int main(int argc, char **argv) {
    int test = -1234567891;
    cout << reverseDigits(test) << '\n';
    return 0;
}
