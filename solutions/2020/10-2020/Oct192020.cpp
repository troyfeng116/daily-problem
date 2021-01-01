#include <iostream>
#include <vector>
using namespace std;

/*
Given an array of characters with repeats, compress it in place. The length after compression should be 
less than or equal to the original array.

Example:
Input: ['a', 'a', 'b', 'c', 'c', 'c']
Output: ['a', '2', 'b', 'c', '3']
*/

void print(vector<char> arr) {
    std::cout << "[";
    for (int i = 0; i < arr.size()-1; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[arr.size()-1] << "]\n";
}

/* APPROACH 1: Only compress if >= 2 characters in a row. 'a'->'a1' is no good. O(N) time, O(N) space */
vector<char> compress(vector<char> &arr) {
    int n = arr.size();
    vector<char> compressed;
    for (int i = 0; i < n; i++) {
        char c = arr[i];
        int count = 1;
        while (i+1 < n && arr[i+1] == c) {
            i++;
            count++;
        }
        compressed.push_back(c);
        if (count > 1) {
            string countString = to_string(count);
            for (int j = 0; j < countString.length(); j++) {
                compressed.push_back(countString.at(j));
            }
        }
    }
    return compressed;
}

/* APPROACH 2: O(1) space */
void compress2(vector<char> &arr) {
    int n = arr.size();
    int l = 0;
    for (int i = 0; i < n; i++) {
        int c = arr[i];
        int count = 1;
        while (i+1 < n && arr[i+1] == c) {
            i++;
            count++;
        }
        arr[l] = c;
        l++;
        if (count > 1) {
            string countString = to_string(count);
            for (int j = 0; j < countString.length(); j++) {
                arr[l] = countString.at(j);
                l++;
            }
        }
    }
    for (int i = 0; i < n-l; i++) arr.pop_back();
}

int main(int argc, char **argv) {
    vector<char> arr = {'a', 'a', 'b', 'c', 'c', 'c'};
    print(compress(arr));
    compress2(arr);
    print(arr);
    return 0;
}
