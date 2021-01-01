#include <iostream>
using namespace std;

/*
Return the longest run of 1s for a given integer n's binary representation.

Example:
Input: 242
Output: 4
242 in binary is 0b11110010, so the longest run of 1 is 4.
*/

/* APPROACH 1: Comvert to binary and track consecutive 1s. */
int longestConsecutiveOnes(int num) {
    int maxLen = 0;
    int curLen = 0;
    while (num != 0) {
        if (num%2 == 1) curLen++;
        else {
            maxLen = max(maxLen, curLen);
            curLen = 0;
        }
        num /= 2;
    }
    return max(maxLen, curLen);
}

/* APPROACH 2: Use bitwise operators. num & (num << 1) reduces length of every sequence of 1s by
one. */
int longestConsecutiveOnes2(int num) {
    int maxLen = 0;
    while (num != 0) {
        num = num & (num << 1);
        maxLen++;
    }
    return maxLen;
}

int main(int argc, char **argv) {
    int num = 242;
    std::cout << "APPROACH 1 TESTING: " << longestConsecutiveOnes(num) << '\n';
    std::cout << "APPROACH 2 TESTING: " << longestConsecutiveOnes2(num) << '\n';
    return 0;
}
