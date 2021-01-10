#include <iostream>
#include <string>
using namespace std;

/*
Given a non-negative integer n, convert n to base 2 in string form. Do not use any built in
base 2 conversion functions.
*/

/* APPROACH 1: Standard base 2 conversion. O(log N) */
string toBase2(int n) {
    string ans = "";
    while (n != 0) {
        ans = to_string(n % 2) + ans;
        n /= 2;
    }
    return ans;
}

int main(int argc, char **argv) {
    int n = 123;
    cout << toBase2(n) << '\n';
    return 0;
}
