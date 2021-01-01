#include <iostream>
#include <string>
using namespace std;

/*
Version numbers are strings that are used to identify unique states of software products. A version number 
is in the format a.b.c.d. and so on where a, b, etc. are numeric strings separated by dots. These generally 
represent a hierarchy from major to minor changes. Given two version numbers version1 and version2, 
conclude which is the latest version number. Your code should do the following:

If version1 > version2 return 1.
If version1 < version2 return -1.
Otherwise return 0.

Note that the numeric string s such as a, b, c, d, etc. may have leading zeroes, and that the version 
strings do not start or end with dots. Unspecified level revision numbers default to 0.

Example:
Input: 
version1 = "1.0.33"
version2 = "1.0.27"
Output: 1 
#version1 > version2

Input:
version1 = "0.1"
version2 = "1.1"
Output: -1
#version1 < version2

Input: 
version1 = "1.01"
version2 = "1.001"
Output: 0
#ignore leading zeroes, 01 and 001 represent the same number. 

Input:
version1 = "1.0"
version2 = "1.0.0"
Output: 0
#version1 does not have a 3rd level revision number, which
defaults to "0"
*/

/* APPROACH 1: walk through both strings and stop at . character. O(N+M) (sum of lengths) */
// Given i = 0 or v[i-1] = '.', find this portion of the version number and leave i at next '.' or end of string.
int getNumber(string v, int &i, int n) {
    // Ignore leading zeroes
    int ans = 0;
    while (i < n && v[i] != '.' && v[i] == '0') i++;
    while (i < n && v[i] != '.') {
        ans *= 10; 
        ans += v[i] - '0';
        i++;
    }
    return ans;
}
int compareVersionNumbers(string v1, string v2) {
    int n1 = v1.length(), n2 = v2.length();
    int i1 = 0, i2 = 0;
    int num1 = 0, num2 = 0;
    while (i1 < n1 && i2 < n2) {
        num1 = getNumber(v1, i1, n1);
        num2 = getNumber(v2, i2, n2);
        int res = num1 - num2;
        if (res != 0) return res/abs(res);
        i1++;
        i2++;
    }
    while (i1 < n1) {
        num1 = getNumber(v1, i1, n1);
        num2 = 0;
        int res = num1-num2;
        if (res != 0) return res/abs(res);
        i1++;
    }
    while (i2 < n2) {
        num1 = 0;
        num2 = getNumber(v2, i2, n2);
        int res = num1-num2;
        if (res != 0) return res/abs(res);
        i2++;
    }
    return 0;
}

int main(int argc, char **argv) {
    string v1 = "1.0";
    string v2 = "1.0.0";
    std::cout << compareVersionNumbers(v1, v2) << '\n';
    return 0;
}
