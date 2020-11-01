#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

/*
You are given an array of integers. Return the length of the longest consecutive elements sequence in the 
array.

For example, the input array [100, 4, 200, 1, 3, 2] has the longest consecutive sequence 1, 2, 3, 4, and 
thus, you should return its length, 4.

Expected O(N).
*/

/* APPROACH 1: Sort, then one pass and keep track of longest consecutive sequence. O(N log N) */
int longestConsecutiveSequence(vector<int> &arr) {
    int n = arr.size();
    sort(arr.begin(), arr.end());
    int maxLength = 0;
    for (int i = 0; i < n; i++) {
        int count = 1;
        // >= to handle duplicates
        while (i < n-1 && arr[i]+1 >= arr[i+1]) {
            if (arr[i]+1 == arr[i+1]) count++;
            i++;
        }
        maxLength = max(count, maxLength);
    }
    return maxLength;
}

/* APPROACH 2: Hash all numbers in arr. Then iterate over starting points. If set does not contain
start-1, iterate start and track length.
Initial hash O(N). Iterate over starting points O(N). For each starting point, we would iterate over some 
consecutive subsequence. Since there are at most N consecutive integers in arr, all the iterations can be
at most O(N). Total O(N) time O(N) space */
int longestConsecutiveSequence2(vector<int> &arr) {
    int n = arr.size();
    unordered_set<int> set;
    for (int i = 0; i < n; i++) set.insert(arr[i]);
    int maxLength = 0;
    for (int i = 0; i < n; i++) {
        int element = arr[i];
        if (element >= INT_MIN+1 && set.count(element-1) == 0) {
            while (element <= INT_MAX-1 && set.count(element+1) > 0) element++;
        }
        maxLength = max(maxLength, element - arr[i] + 1);
    }
    return maxLength;
}

int main(int argc, char **argv) {
    vector<int> test1 = {100, 4, 200, 1, 3, 2};
    std::cout << longestConsecutiveSequence(test1) << '\n';
    vector<int> test2 = {100, 4, 200, 1, 3, 2};
    std::cout << longestConsecutiveSequence2(test2) << '\n';
    return 0;
}
