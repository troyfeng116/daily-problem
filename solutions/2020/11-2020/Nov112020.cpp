#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
An IP Address is in the format of A.B.C.D, where A, B, C, D are all integers between 0 to 255.

Given a string of numbers, return the possible IP addresses you can make with that string by splitting into 
4 parts of A, B, C, D.

Keep in mind that integers can't start with a 0! (Except for 0)

Example:
Input: 1592551013
Output: ['159.255.101.3', '159.255.10.13']
*/

void print(vector<string> arr) {
    std::cout << "[";
    for (int i = 0; i < arr.size()-1; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[arr.size()-1] << "]\n";
}

/* APPROACH 1: Recursion (dfs). Exponential time */
// Assume either i = 0 or we just added a number ending at i-1.
void recurse(string num, int n, int i, int numUsed, string soFar, vector<string> &ans) {
    if (i >= n) {
        if (numUsed == 4) ans.push_back(soFar.substr(0, soFar.length() - 1));
        return;
    }
    if (numUsed >= 4) return;
    // No leading zeroes.
    if (num[i] == '0') {
        recurse(num, n, i+1, numUsed+1, soFar+"0.", ans);
        return;
    }
    int nextNum = 0;
    // Only need to check three digits from i.
    for (int j = i; j < i+3 && j < n; j++) {
        nextNum = nextNum*10 + num[j] - '0';
        if (nextNum <= 255) {
            recurse(num, n, j+1, numUsed+1, soFar + to_string(nextNum) + '.', ans);
        }
    }
}
vector<string> getIPAddresses(string num) {
    vector<string> ans;
    recurse(num, num.length(), 0, 0, "", ans);
    return ans;
}

int main(int argc, char **argv) {
    string num = "1592551013";
    print(getIPAddresses(num));
    return 0;
}
