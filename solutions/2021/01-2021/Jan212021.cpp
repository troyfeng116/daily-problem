#include <iostream>
#include <string>
using namespace std;

/*
Given two strings which represent non-negative integers, multiply the two numbers and return
the product as a string as well. You should assume that the numbers may be sufficiently large
such that the built-in integer type will not be able to store the input.
*/

/* APPROACH 1: Multiply num by one digit at a time, and then add all the results (just like
normal long multiplication). When handling string nums, keep them reversed to simplify things.
O(M * N) */
string reverse(string x) {
    string ans = "";
    for (int i = 0; i < x.length(); i++) {
        ans = x[i] + ans;
    }
    return ans;
}
string padZero(string x, int numZeroes) {
    string ans = x;
    for (int i = 0; i < numZeroes; i++) ans = '0' + ans;
    return ans;
}
string add(string x, string y) {
    string ans = "";
    int i = 0, carry = 0;
    while (i < x.length() && i < y.length()) {
        int res = x[i] + y[i] - '0' - '0' + carry;
        ans += to_string(res % 10);
        carry = res >= 10 ? 1 : 0;
        i++;
    }
    while (i < x.length()) {
        int res = x[i] - '0' + carry;
        ans += to_string(res % 10);
        carry = res >= 10 ? 1 : 0;
        i++;
    }
    while (i < y.length()) {
        int res = y[i] - '0' + carry;
        ans += to_string(res % 10);
        carry = res >= 10 ? 1 : 0;
        i++;
    }
    if (carry != 0) ans += to_string(carry);
    return ans;
}
string multiplyOneDigit(string x, int digit) {
    string ans = "";
    int carry = 0;
    for (int i = 0; i < x.length(); i++) {
        int res = (x[i] - '0') * digit + carry;
        ans += to_string(res % 10);
        carry = res / 10;
    }
    if (carry != 0) ans += to_string(carry);
    return ans;
}
string multiply(string x, string y) {
    string x2 = reverse(x), y2 = reverse(y);
    string ans = "";
    for (int place = 0; place < y2.length(); place++) {
        string toAdd = multiplyOneDigit(x2, y2[place] - '0');
        toAdd = padZero(toAdd, place);
        ans = add(ans, toAdd);
    }
    return reverse(ans);
}

int main(int argc, char **argv) {
    string x = "12345", y = "99999899";
    std::cout << multiply(x, y) << '\n';
    return 0;
}
