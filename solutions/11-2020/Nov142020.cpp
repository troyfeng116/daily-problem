#include <iostream>
using namespace std;

/* Given an integer, check if that integer is a palindrome. For this problem do not convert the 
integer to a string to check if it is a palindrome. */

/* APPROACH 1: Check if digits mirror each other. */
bool isPalindrome(int num) {
    if (num < 0) return false;
    int powTen = 1;
    while (powTen <= INT_MAX / 10 && powTen * 10 <= num) powTen *= 10;
    while (num != 0) {
        int last = num%10;
        int first = num/powTen;
        if (last != first) return false;
        if (num >= powTen) num -= first * powTen;
        num /= 10;
        powTen /= 100;
    }
    return true;
}

/* APPROACH 2: Reverse half of the number. If odd #digits, reversed will have one extra digit
at the end we can throw away. Special case is numbers ending in 0: return false. */
bool isPalindrome2(int num) {
    if (num < 0) return false;
    if (num == 0) return true;
    if (num % 10 == 0) return false;
    int reversed = 0;
    while (num > reversed) {
        reversed = reversed*10 + num%10;
        num /= 10;
    }
    return num == reversed || num == reversed/10;
}

int main(int argc, char **argv) {
    std::cout << "APPROACH 1 TESTING: " << isPalindrome(1034301) << '\n';
    std::cout << "APPROACH 2 TESTING: " << isPalindrome2(1034301) << '\n';
    return 0;
}
