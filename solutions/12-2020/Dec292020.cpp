#include <iostream>
#include <string>
using namespace std;

/*
Given a string, convert it to an integer without using the builtin str function.

Consider all possible cases of an integer. In the case where the string is not a valid integer,
return None.
*/

/*
QUESTIONs: 
-leading/trailing space? Will assume no for simplicity
-need to handle int overflow? Will assume no for simplicity
*/

/* APPROACH 1: Build from ASCII. O(len) */
int mySToI(string str) {
    int ans = 0;
    bool negative = str[0] == '-';
    int i = negative ? 1 : 0;
    for (; i < str.length(); i++) {
        int c = str[i] - '0';
        if (c < 0 || c > 9) {
            std::cout << "NaN\n";
            return -1;
        }
        ans = ans * 10 + c;
    }
    return negative ? -ans : ans;
}

int main(int argc, char **argv) {
    string test = "-12345";
    std::cout << mySToI(test) << '\n';
    return 0;
}
