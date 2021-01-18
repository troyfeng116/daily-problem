#include <iostream>
#include <unordered_map>
using namespace std;

/*
Given a numerator and a denominator, find what the equivalent decimal representation is
as a string. If the decimal representation has recurring digits, then put those digits
in brackets (ie 4/3 should be represented by 1.(3) to represent 1.333...). Do not use
any built in evaluator functions. You can also assume that the denominator will be
nonzero.
*/

/* APPROACH 1: simulate long division, keeping track of numerator and map of index of each
spot where each modulus occurred. Once repeat detected, add brackets to index in map.
O(N) time + space, where N = num digits in terminating representation or cycle. */
string fracToDecimal(int num, int denom) {
    string result = to_string(num / denom);
    num = abs(num), denom = abs(denom);
    if (num % denom == 0) return result;
    result += '.';
    unordered_map<int, int> map;
    num = num % denom;
    while (num != 0) {
        if (map.find(num) != map.end()) {
            int i = map[num];
            result = result.substr(0, i) + '(' + result.substr(i) + ')';
            break;
        }
        map[num] = result.length();
        num *= 10;
        result += to_string(num / denom);
        num = num % denom;
    }
    return result;
}

int main(int argc, char **argv) {
    int num = 1;
    int denom = 61;
    std::cout << fracToDecimal(num, denom) << '\n';
    return 0;
}
