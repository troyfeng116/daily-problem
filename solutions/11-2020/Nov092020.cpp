#include <iostream>
#include <string>
using namespace std;

/*
MS Excel column titles have the following pattern: A, B, C, ..., Z, AA, AB, ..., AZ, BA, BB, ..., ZZ, 
AAA, AAB, ... etc. In other words, column 1 is named "A", column 2 is "B", column 26 is "Z", column 27 
is "AA" and so forth. Given a positive integer, find its corresponding column name.

Examples:
Input: 26
Output: Z

Input: 51
Output: AY

Input: 52
Output: AZ

Input: 676
Output: YZ

Input: 702
Output: ZZ

Input: 704
Output: AAB

*/

/* APPROACH 1: Convert to base 26 and utilize ASCII. Note each place is off by 1 (since starts at col 1). */
string intToExcelCol(int num) {
    string ans = "";
    while (num > 0) {
        num--;
        ans += num%26 + 'A';
        num /= 26;
    }
    reverse(ans.begin(), ans.end());
    return ans;
}

/* APPROACH 2: Base conversion but with recursion. */
string intToExcelCol2(int num) {
    string ch = "";
    int remainder = num % 26;
    if (remainder == 0) remainder = 26;
    ch += 'A' + remainder - 1;
    num -= remainder;
    if (num / 26 > 0) return intToExcelCol2(num/26).append(ch);
    return ch;
}

int main(int argc, char **argv) {
    std::cout << "APPROACH 1 TESTING: " << intToExcelCol(52) << '\n';
    std::cout << "APPROACH 2 TESTING: " << intToExcelCol2(52) << '\n';
    return 0;
}
