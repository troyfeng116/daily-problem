#include <iostream>
#include <string>
using namespace std;

/*
In many spreadsheet applications, the columns are marked with letters. From the 1st to the 26th 
column the letters are A to Z. Then starting from the 27th column it uses AA, AB, ..., ZZ, AAA, 
etc.

Given a number n, find the n-th column name.
*/

/* Uh, see Nov 9 problem... So here's a function to go from column to int. */
int columnTitleToInt(string str) {
    int ans = 0;
    for (int i = 0; i < str.length(); i++) {
        ans *= 26;
        ans += str[i] - 'A' + 1;
    }
    return ans;
}

/* APPROACH 1: Base conversion with ASCII (see 11/9 problem). */
string intToColumnTitle(int num) {
    string ans = "";
    while (num > 0) {
        int remainder = num % 26;
        if (remainder == 0) remainder = 26;
        ans = (char) (remainder + 'A' - 1) + ans;
        num--;
        num /= 26;
    }
    return ans;
}

/* APPROACH 2: Base conversion with ASCII but with recursion (see 11/9). */
string intToColumnTitle2(int num) {
    string ch = "";
    if (num == 0) return ch;
    num--;
    ch += num%26 + 'A';
    return intToColumnTitle2(num/26) + ch;
}

int main(int argc, char **argv) {
    string columnTitle = "AZ";
    int res = columnTitleToInt(columnTitle);
    std::cout << "EXPECTED: " << columnTitle << " = " << res << '\n';

    std::cout << "APPROACH 1: " << intToColumnTitle(res) << '\n';
    std::cout << "APPROACH 2: " << intToColumnTitle2(res) << '\n';
    return 0;
}
