#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

/*
Given two arrays, write a function to compute their intersection - the intersection means 
the numbers that are in both arrays.

Example 1:
Input: nums1 = [1,2,2,1], nums2 = [2,2]
Output: [2]

Example 2:
Input: nums1 = [4,9,5], nums2 = [9,4,9,8,4]
Output: [9,4]

Note:
Each element in the result must be unique.
The result can be in any order.
*/

void print(vector<int> arr) {
    std::cout << "[";
    for (int i = 0; i < arr.size()-1; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[arr.size()-1] << "]\n";
}

/* APPROACH 1: Hash one array's values in set, check other array's values against set.
O(N) space, O(N+M) time. */
vector<int> findIntersection(vector<int> nums1, vector<int> nums2) {
    unordered_set<int> table;
    for (int i = 0; i < nums1.size(); i++) {
        table.insert(nums1[i]);
    }
    vector<int> intersection;
    for (int i = 0; i < nums2.size(); i++) {
        if (table.count(nums2[i]) > 0) {
            intersection.push_back(nums2[i]);
            table.erase(nums2[i]);
        }
    }
    return intersection;
}

int main(int argc, char **argv) {
    vector<int> nums1 = {4,9,5};
    vector<int> nums2 = {9,4,9,8,4,18,8};
    vector<int> intersection = findIntersection(nums1, nums2);
    print(intersection);
    return 0;
}
