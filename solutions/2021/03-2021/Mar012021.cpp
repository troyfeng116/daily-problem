#include <iostream>
using namespace std;

/*
Given a number like 159, add the digits repeatedly until you get a single-digit number.

For instance, 1 + 5 + 9 = 15.
1 + 5 = 6.

So the answer is 6.
*/

/* APPROACH 1: recursion. */
int addDigits(int n) {
    if (n < 10) return n;
    int sumDigits = 0;
    while (n != 0) {
        sumDigits += n % 10;
        n /= 10;
    }
    return addDigits(sumDigits);
}

/* APPROACH 2: sum of digits pattern. O(1) */
int addDigits2(int n) {
    if (n == 0) return 0;
    if (n % 9 == 0) return 9;
    return n % 9;
}

int main(int argc, char **argv) {
    int n = 159;
    cout << "APPROACH 1 TESTING: " << addDigits(n) << '\n';
    cout << "APPROACH 2 TESTING: " << addDigits2(n) << '\n';
    return 0;
}