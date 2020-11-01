#include <iostream>
#include <vector>
using namespace std;

/*
Given an array of integers of size n, where all elements are between 1 and n inclusive, find all of the 
elements of [1, n] that do not appear in the array. Some numbers may appear more than once.

Example:
Input: [4,5,2,6,8,2,1,5]
Output: [3,7]
*/

void print(vector<int> arr) {
    std::cout << "[";
    for (int i = 0; i < arr.size()-1; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[arr.size()-1] << "]\n";
}

/* APPROACH 1: Use an array of booleans as hashmap. O(N) time and space */
vector<int> missingInts(vector<int> nums) {
    int n = nums.size();
    vector<bool> found(n, false);
    for (int i = 0; i < n; i++) {
        found[nums[i]-1] = true;
    }
    vector<int> missing;
    for (int i = 0; i < n; i++) {
        if (!found[i]) missing.push_back(i+1);
    }
    return missing;
}

/* APPROACH 2: Assuming we can modify input array, use original space as hashmap since there are N elements.
We can use +/- to flag found/missing numbers. If i:[1,n] found, set arr[i-1] to negative.
O(N) time, O(1) space */
vector<int> missingInts2(vector<int> nums) {
    int n = nums.size();
    for (int i = 0; i < nums.size(); i++) {
        if (nums[abs(nums[i])-1] > 0) nums[abs(nums[i])-1] *= -1;
    }
    vector<int> missing;
    for (int i = 0; i < n; i++) {
        if (nums[i] > 0) missing.push_back(i+1);
    }
    return missing;
}

/* APPROACH 3: In-place sort. Elements are guaranteed [1,n] and array has n spots. For each element that
isn't in sorted spot, start chain of swaps. O(N) */
vector<int> missingInts3(vector<int> nums) {
    int n = nums.size();
    for (int i= 0; i < n; i++) {
        while (nums[i] != i+1 && nums[nums[i]-1] != nums[i]) {
            swap(nums[i], nums[nums[i]-1]);
        }
    }
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (nums[i] != i+1) ans.push_back(i+1);
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<int> nums = {4,5,2,6,8,2,1,5};
    std::cout << "APPROACH 1 TESTING: ";
    print(missingInts(nums));
    std::cout << "APPROACH 2 TESTING: ";
    print(missingInts2(nums));
    std::cout << "APPROACH 3 TESTING: ";
    print(missingInts3(nums));
    return 0;
}
