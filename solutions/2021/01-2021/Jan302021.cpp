#include <iostream>
#include <string>
using namespace std;

/*
Given two binary numbers represented as strings, return the sum of the two binary numbers as a new binary
represented as a string. Do this without converting the whole binary string into an integer.

ex. "11101" + "1011" = "101000"
*/

/* APPROACH 1: ripple carry adder. O(N) */
string addBinary(string x, string y) {
    int i = x.length() - 1, j = y.length() - 1, sum = 0;
    string ans = "";
    while (i >= 0 || j >= 0 || sum == 1) {
        if (i >= 0) sum += x[i] - '0';
        if (j >= 0) sum += y[j] - '0';
        ans = to_string(sum % 2) + ans;
        sum /= 2;
        i--;
        j--;
    }
    return ans;
}

int main(int argc, char **argv) {
    string x = "11101", y = "1011";
    cout << addBinary(x, y) << '\n';
    return 0;
}
