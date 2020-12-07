#include <iostream>
#include <string>
using namespace std;

/*
Given a 32 bit integer, reverse the bits and return that number.

Example:
Input: 1234 
# In bits this would be 0000 0000 0000 0000 0000 0100 1101 0010
Output: 1260388352
# Reversed bits is 0100 1011 0010 0000 0000 0000 0000 0000
*/

/* APPROACH 1: To string and reverse. */
uint32_t reverseBits(uint32_t num) {
    uint32_t ans = 0;
    int pow = 31;
    while (num != 0) {
        ans += (num % 2) << pow;
        num /= 2; // num = num >> 1;
        pow--;
    }
    return ans;
}

/* APPROACH 2: Kinda like merging. Split into 16 bits, switch L and R. Then swap each 16-bit chunk into
2 bytes, switch L and R of each of those, etc. Use & to mask each L/R chunks and | to "merge". */
uint32_t reverseBits2(uint32_t num) {
    // Move left 16-bit chunk to right, merge with right 16-bit chunk shifted left
    num = (num >> 16) | (num << 16);
    // Move left 8-bit chunks to right, merge with right 8-bit chunks shifted left
    num = ((num & 0xff00ff00) >> 8) | ((num & 0x00ff00ff) << 8);
    // Move left 4-bit chunks to right, merge with right 4-bit chunks shifted left
    num = ((num & 0xf0f0f0f0) >> 4) | ((num & 0x0f0f0f0f) << 4);
    // Move left 2-bit chunks to right, merge with right 2-bit chunks shifted left
    num = ((num & 0xcccccccc) >> 2) | ((num & 0x33333333) << 2);
    // Move left 1-bit chunks to right, merge with right 1-bit chunks shifted left
    num = ((num & 0xaaaaaaaa) >> 1) | ((num & 0x55555555) << 1);
    return num;
}

int main(int argc, char **argv) {
    std::cout << "APPROACH 1: " << reverseBits(1234) << '\n';
    std::cout << "APPROACH 2: " << reverseBits2(1234) << '\n';
    return 0;
}
