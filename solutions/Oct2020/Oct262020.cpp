#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

/* You are given an array of integers, and an integer K. Return the subarray which sums to K. You can 
assume that a solution will always exist. */

/* QUESTION: can we assume all integers are positive? will assume no (if all non-negative, can use sliding
window) */

void print(vector<int> arr) {
    std::cout << "[";
    for (int i = 0; i < arr.size()-1; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[arr.size()-1] << "]\n";
}

/* APPROACH 1: Brute force. For each starting point, for each subarray, check cumulative sum. O(N^2) */
vector<int> findContiguousSubarray(vector<int> nums, int target) {
    for (int i = 0; i < nums.size(); i++) {
        int sum = 0;
        for (int j = i; j < nums.size(); j++) {
            sum += nums[j];
            if (sum == target) return vector<int>(nums.begin()+i, nums.begin()+j+1);
        }
    }
    return vector<int>();
}

/* APPROACH 2: We can generate all contiguous subarrays nums[i,j] by subtracting nums[0,i) from nums[0,j].
So if we store cumulative sums in sums[], where sums[i] = sum(nums[0,i]), and hash each cumulative sum
in a hashmap, it would be like finding whether 1+ elements subtract to target, which is O(N) with hash.
In hashmap, store cumulative sum along with vector of indices i such that SUM(arr[0,i] = cSum.
O(N) time and space */
vector<int> findContiguousSubarray2(vector<int> nums, int target) {
    unordered_map<int, vector<int> > table;
    int sum = 0;
    vector<int> sums;
    table[0].push_back(0);
    for (int i = 0; i < nums.size(); i++) {
        sum += nums[i];
        table[sum].push_back(i);
        sums.push_back(sum);
    }
    for (int i = 0; i < sums.size(); i++) {
        if (table[target + sums[i]].size() > 0) {
            int j = table[target + sums[i]][0];
            return vector<int>(nums.begin()+min(i,j)+1, nums.begin()+max(i,j)+1);
        }
    }
    return vector<int>();
}

int main(int argc, char **argv) {
    vector<int> nums = {1, 3, 2, 5, 7, 2};
    int target = 14;
    print(findContiguousSubarray(nums, target));
    print(findContiguousSubarray2(nums, target));
    return 0;
}
