#include <iostream>
#include <string>
using namespace std;

/*
Given a string, you need to reverse the order of characters in each word within a 
sentence while still preserving whitespace and initial word order.

Example 1:
Input: "The cat in the hat"
Output: "ehT tac ni eht tah"
Note: In the string, each word is separated by single space and there will not be any 
extra space in the string.
*/

/* APPROACH 1: Turn to char array and reverse each word. O(N) time + space */
void reverse(char arr[], int l, int r) {
    for (int i = l; i <= (l+r)/2; i++) {
        char temp = arr[i];
        arr[i] = arr[r-i+l];
        arr[r-i+l] = temp;
    }
}
string reverseWords(string sentence) {
    int len = sentence.length();
    char *arr = new char[len];
    for (int i = 0; i < len; i++) {
        arr[i] = sentence.at(i);
    }
    int l = 0;
    int r = 0;
    while (r < sentence.length()) {
        while (r < sentence.length() && sentence.at(r) != ' ') r++;
        reverse(arr, l, r-1);
        l = r+1, r++;
    }
    string ans = "";
    for (int i = 0; i < len; i++) ans.push_back(arr[i]);
    return ans;
}

int main(int argc, char **argv) {
    string sentence = "The cat in the hat!";
    std::cout << reverseWords(sentence) << '\n';
    return 0;
}
