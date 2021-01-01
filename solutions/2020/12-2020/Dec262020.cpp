#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
Given a list of words in a string, reverse the words in-place (i.e. don't create a new string and reverse
the words). You can assume the input will be a mutable sequence (like vector).

ex.
"can you read this" => "this read you can"
*/

/* QUESTION: leading/trailing spaces? Will assume no for simplicity */

void print(vector<char> arr) {
    for (int i = 0; i < arr.size(); i++) {
        std::cout << arr[i];
    }
    std::cout << '\n';
}

/* APPROACH 1: Reverse whole string, then re-reverse individual words. O(N) time, O(1) space */
// Reverse str[l,r).
void reverse(vector<char> &str, int l, int r) {
    for (int i = l; i < (l+r)/2; i++) {
        int temp = str[i];
        str[i] = str[r - i + l - 1];
        str[r - i + l - 1] = temp;
    }
}
void reverseWords(vector<char> &str) {
    int n = str.size();
    reverse(str, 0, n);
    int l = 0, r = 0;
    while (l < n) {
        while (r < n && str[r] != ' ') r++;
        reverse(str, l, r);
        r++;
        l = r;
    }
}

int main(int argc, char **argv) {
    string str = "can you read this";
    vector<char> list;
    for (int i = 0; i < str.length(); i++) {
        list.push_back(str[i]);
    }

    reverseWords(list);
    print(list);
    return 0;
}