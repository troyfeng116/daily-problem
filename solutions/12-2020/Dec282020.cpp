#include <iostream>
using namespace std;

/*
Given a 32-bit integer, swap the 1st and 2nd bit, 3rd and 4th bit, up til the 31st and 32nd bit.
*/

/* APPROACH 1: extract bits one by one and construct swapped bits. */
int swapBits(int num) {
    int reversedAns = 0;
    while (num != 0) {
        int rMost = num % 2;
        num /= 2;
        int rMost2 = num % 2;
        num /= 2;
        reversedAns = reversedAns * 2 + rMost2;
        reversedAns = reversedAns * 2 + rMost;
    }
    int ans = 0;
    while (reversedAns != 0) {
        ans = ans * 2 + (reversedAns % 2);
        reversedAns /= 2;
    }
    return ans;
}

/* APPROACH 2: reversing bits is equivalent to shifting 0, 2, 4, ..., 32 bits one spot to the right
and 1, 3, 5, ..., 31 bits one bit to the left, extracting only every other bit from each result,
and then "merging" those results. We can use the bitwise shift operators and bitmasks to achieve
this. */
int swapBits2(int num) {
    int leftBits = (num << 1) & 0xaaaaaaaa; // shift to the left, mask is 10101010... 
    int rightBits = (num >> 1) & 0x55555555; // shift to the right, mask is 01010101...
    return leftBits | rightBits;
}

int main(int argc, char **argv) {
    int num = 42;
    std::cout << "APPROACH 1: " << swapBits(num) << '\n';
    std::cout << "APPROACH 2: " << swapBits2(num) << '\n';
    return 0;
}
