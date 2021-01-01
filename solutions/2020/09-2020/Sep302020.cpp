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

/* APPROACH 2: Sort smaller array first, then binary search. O(min((M+N)logN, (M+N)log(M))) */
int search(vector<int> nums, int target, int l, int r) {
    if (l > r) return -1;
    int m = (l+r)/2;
    if (target < nums[m]) return search(nums, target, l, m-1);
    if (target > nums[m]) return search(nums, target, m+1, r);
    return m;
}
vector<int> findIntersection2(vector<int> nums1, vector<int> nums2) {
    unordered_set<int> found;
    vector<int> intersection;
    int m = nums1.size(), n = nums2.size();
    if (m < n) {
        std::sort(nums1.begin(), nums1.end());
        for (int i = 0; i < n; i++) {
            if (search(nums1, nums2[i], 0, m-1) >= 0 && found.count(nums2[i]) == 0) {
                found.insert(nums2[i]);
                intersection.push_back(nums2[i]);
            }
        }
    }
    else {
        std::sort(nums2.begin(), nums2.end());
        for (int i = 0; i < m; i++) {
            if (search(nums2, nums1[i], 0, n-1) >= 0 && found.count(nums1[i]) == 0) {
                found.insert(nums1[i]);
                intersection.push_back(nums1[i]);
            }
        }
    }
    return intersection;
}

int main(int argc, char **argv) {
    vector<int> nums1 = {4,9,5};
    vector<int> nums2 = {9,4,9,8,4,18,8};
    vector<int> intersection = findIntersection(nums1, nums2);
    print(intersection);
    vector<int> intersection2 = findIntersection2(nums1, nums2);
    print(intersection);
    return 0;
}
