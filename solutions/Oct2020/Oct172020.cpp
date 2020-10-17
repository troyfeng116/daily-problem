#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/*
Given an array of integers, arr, where all numbers occur twice except one number which occurs once, find the number. 
Your solution should ideally be O(n) time and use constant extra space.
Example:
Input: arr = [7, 3, 5, 5, 4, 3, 4, 8, 8]
Output: 7
*/

/* APPROACH 1: Hash map. O(N) time and space */
int findUnique(vector<int> nums) {
    unordered_map<int,int> table;
    for (int i = 0; i < nums.size(); i++) {
        int c = table.count(nums[i]);
        table.emplace(nums[i], c+1);
    }
    for (int i = 0; i < nums.size(); i++) {
        if (table.count(nums[i]) == 1) return nums[i];
    }
    std::cout << "BAD INPUT: NO SINGLE OCCURRENCE\n";
    return 0;
}

/* APPROACH 2: Bit xor. If x == y, then x^y = 0, and for all x, x^0 = x. O(N) time */
int findUnique2(vector<int> nums) {
    int XOR = 0;
    for (int i = 0; i < nums.size(); i++) {
        XOR ^= nums[i];
    }
    return XOR;
}

int main(int argc, char **argv) {
    vector<int> nums = {7, 3, 5, 5, 4, 3, 4, 8, 8};
    std::cout << findUnique(nums) << '\n';
    std::cout << findUnique2(nums) << '\n';
    return 0;
}
