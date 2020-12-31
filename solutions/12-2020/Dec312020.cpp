#include <iostream>
using namespace std;

/* Last day of 2020! */

/*
The power function calculates x raised to the nth power. If implemented in O(n) it would
simply be a for loop over n and multiply x n times. Instead implement this power function
in O(log n) time. You can assume that n will be a non-negative integer.
*/

/* QUESTION: handle integer overflow? Will assume no for simplicity. */

/* APPROACH 1: Fast exponentiation. x^n = (x^{n/2}) * (x^{n/2}), with an extra * x if n
is odd. Use recursion.
O(log_2(n)) */
int fastPow(int x, int n) {
    if (n == 0) return 1;
    if (n == 1) return x;
    int sqrt = fastPow(x, n/2);
    return n % 2 == 0 ? sqrt * sqrt : sqrt * sqrt * x;
}

/* APPROACH 2: Same as approach 1 but iterative. O(log_2(n)) */
int fastPow2(int x, int n) {
    int ans = 1;
    while (n > 0) {
        if (n % 2 == 1) ans *= x;
        n /= 2;
        x = x * x;
    }
    return ans;
}

int main(int argc, char **argv) {
    int x = 5, n = 6;
    std::cout << "APPROACH 1 TESTING: " << fastPow(x, n) << '\n';
    std::cout << "APPROACH 2 TESTING: " << fastPow2(x, n) << '\n';\
    return 0;
}
