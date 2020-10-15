#include <iostream>
#include <vector>
using namespace std;

/*
Given a list of numbers of size n, where n is greater than 3, find the maximum and minimum of the list using
less than 2 * (n - 1) comparisons.
*/

struct Pair {
    int min;
    int max;
};

/* APPROACH 1: Pretty much linear, but reduce one comparison at beginning. Worst
2n-1, best case n-1 compares (for sorted descending and ascending, respectively) */
Pair getMinAndMax1(vector<int> nums) {
    struct Pair ans;
    if (nums[0] < nums[1]) {
        ans.min = nums[0];
        ans.max = nums[1];
    }
    else {
        ans.min = nums[1];
        ans.max = nums[0];
    }
    for (int i = 2; i < nums.size(); i++) {
        if (nums[i] > ans.max) ans.max = nums[i];
        else if (nums[i] < ans.min) ans.min = nums[i];
    }
    return ans;
}

/* APPROACH 2: We only need one compare to find min/max of two elements. So we
can split our array up into pairs and reduce the number of comparisons. We don't
need to check every element for min and max.
Avg 3n/2 - 2. */
Pair getMinAndMax2(vector<int> nums) {
    Pair ans;
    int n = nums.size();
    int i = 0;
    if (n%2 == 0) {
        if (nums[0] < nums[1]) {
            ans.min = nums[0];
            ans.max = nums[1];
        }
        else {
            ans.min = nums[1];
            ans.max = nums[0];
        }
        i = 2;
    }
    else {
        ans.min = nums[0];
        ans.max = nums[0];
        i = 1;
    }
    while (i < n-1) {
        if (nums[i] > nums[i+1]) {
            if (nums[i] > ans.max) ans.max = nums[i];
            if (nums[i+1] < ans.min) ans.min = nums[i+1];
        }
        else {
            if (nums[i+1] > ans.max) ans.max = nums[i+1];
            if (nums[i] < ans.min) ans.min = nums[i];
        }
        i += 2;
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<int> test = {3, 5, 1, 2, 4, 8};
    Pair result1 = getMinAndMax1(test);
    std::cout << "MIN: " << result1.min << ", MAX: " << result1.max << '\n';
    Pair result2 = getMinAndMax2(test);
    std::cout << "MIN: " << result2.min << ", MAX: " << result2.max << '\n';
    return 0;
}
