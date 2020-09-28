#include <iostream>
#include <vector>
#include <string>
using namespace std;

/*
Given a sorted list of numbers, return a list of strings that represent all of the consecutive 
numbers.

Example:
Input: [0, 1, 2, 5, 7, 8, 9, 9, 10, 11, 15]
Output: ['0->2', '5->5', '7->11', '15->15']
Assume that all numbers will be greater than or equal to 0, and each element can repeat.
*/

void print(vector<string> arr) {
    std::cout << "[";
    for (int i = 0; i < arr.size()-1; i++) std::cout << arr[i] + ", ";
    std::cout << arr[arr.size()-1] << "]\n";
}

/* APPROACH 1: Simple 1-pass parse, adding consecutive ints to strings as we go. O(N) time */
vector<string> getConsecutiveIntegers(vector<int> nums) {
    vector<string> ans;
    int start = nums[0];
    int prev = start;
    for (int i = 1; i < nums.size(); i++) {
        if (nums[i] == prev || nums[i] == prev+1) prev = nums[i];
        else {
            ans.push_back(to_string(start)+"->"+to_string(prev));
            start = nums[i];
            prev = nums[i];
        }
    }
    ans.push_back(to_string(start)+"->"+to_string(prev));
    return ans;
}

int main(int argc, char **argv) {
    vector<int> test = {0,1,2,5,7,8,9,9,10,11,12};
    vector<string> res = getConsecutiveIntegers(test);
    print(res);
    return 0;
}
