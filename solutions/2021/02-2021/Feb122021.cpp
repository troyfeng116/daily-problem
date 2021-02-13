#include <iostream>
using namespace std;

/*
Given an integer, find the number of 1 bits it has.

ex. n = 23 -> 4, since 23 = 0b10111
*/

/* APPROACH 1: Peel away bits one at a time. O(#bits) */
int countSetBits(uint32_t n) {
    int count = 0;
    while (n != 0) {
        if (n % 2 == 1) count++;
        n = n >> 1;
    }
    return count;
}

/* APPROACH 2: least-significant set bit mask is n - 1. O(#set bits) = O(log N) */
int countSetBits2(uint32_t n) {
    int count = 0;
    while (n != 0) {
        n = n & (n - 1);
        count++;
    }
    return count;
}

int main(int argc, char **argv) {
    int n = 23;
    cout << "APPROACH 1 TESTING: " << countSetBits(n) << '\n';
    cout << "APPROACH 2 TESTING: " << countSetBits2(n) << '\n';
    return 0;
}
