#include <iostream>
#include <string>
using namespace std;

/*
A look-and-say sequence is defined as the integer sequence beginning with a single digit in 
which the next term is obtained by describing the previous term. An example is easier to 
understand:

Each consecutive value describes the prior value.

1      #
11     # one 1's
21     # two 1's
1211   # one 2, and one 1.
111221 # #one 1, one 2, and two 1's.

Your task is, return the nth term of this sequence.
*/

/* APPROACH 1: All we need is the previous term to generate the next one.
I'll return a string corresponding to the n'th term.
Each step runs in O(length(n)). The terms get really long really quickly */
string nthLookAndSay(int n) {
    string prev = "1";
    for (int term = 1; term < n; term++) {
        int index = 0;
        string cur = "";
        while (index < prev.length()) {
            char digit = prev.at(index);
            int count = 0;
            while(index < prev.length() && prev.at(index) == digit) {
                count++;
                index++;
            }
            cur.append(to_string(count) + "" + digit);
        }
        prev = cur;
    }
    return prev;
}

int main(int argc, char **argv) {
    for (int n = 1; n <= 15; n++) {
        std::cout << nthLookAndSay(n) << '\n';
    }
    return 0;
}
