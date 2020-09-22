#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
using namespace std;

/*
Given an array, nums, of n integers, find all unique triplets (three numbers, a, b, & c) in nums 
such that a + b + c = 0. Note that there may not be any triplets that sum to zero in nums, and 
that the triplets must not be duplicates.

Example:
Input: nums = [0, -1, 2, -3, 1]
Output: [0, -1, 1], [2, -3, 1]
*/

/* QUESTION: Okay to return triples as strings? Will assume yes */

string toStringTriple(int a, int b, int c) {
    return to_string(a) + " " + to_string(b) + " " + to_string(c);
}

/* APPROACH 1: Store triplets in set to avoid duplicates. Fix first element, search for twosum
in rest of array adding to additive inverse by hashing. N first elements, O(N) search for total
of O(N^2) time with O(N^2) space for hashing */
vector<string> findTriples1(int nums[], int n) {
    unordered_set<string> ans;
    for (int f = 0; f < n; f++) {
        unordered_set<int> table;
        for (int s = f+1; s < n; s++) {
            if (table.count(-nums[s]-nums[f])) ans.insert(toStringTriple(nums[f], nums[s], -nums[s]-nums[f]));
            table.insert(nums[s]);
        }
    }
    return vector<string>(ans.begin(), ans.end());
}

/* APPROACH 2: sort, fix first, use two pointers for the second and third. O(N^2) time, O(N)
space */
void sort(int *arr, int l, int r) {
    if (l <= r) {
        int splitter = arr[r];
        int m = l;
        for (int i = l; i < r; i++) {
            if (arr[i] < splitter) {
                int temp = arr[i];
                arr[i] = arr[m];
                arr[m] = temp;
                m++;
            }
        }
        arr[r] = arr[m];
        arr[m] = splitter;
        sort(arr, l, m-1);
        sort(arr, m+1, r);
    }
}
vector<string> findTriples2(int *nums, int n) {
    sort(nums, 0, n-1);
    unordered_set<string> ans;
    for (int f = 0; f < n; f++) {
        int first = nums[f];
        int s = f+1;
        int t = n-1;
        while (s < t) {
            if (nums[s] + nums[t] < -first) s++;
            else if (nums[s] + nums[t] > -first) t--;
            else {
                ans.insert(toStringTriple(first, nums[s], -nums[s]-first));
                s++;
                t--;
            }
        }
    }
    return vector<string>(ans.begin(), ans.end());
}

int main(int argc, char **argv) {
    int n = 5;
    int test1[] = {0,-1,2,-3,1};
    vector<string> res1 = findTriples1(test1, n);
    for (int i = 0; i < res1.size(); i++) {
        std::cout << res1[i] << '\n';
    }

    int test2[] = {0,-1,2,-3,1};
    vector<string> res2 = findTriples2(test2, n);
    for (int i = 0; i < res2.size(); i++) {
        std::cout << res2[i] << '\n';
    }
    return 0;
}
