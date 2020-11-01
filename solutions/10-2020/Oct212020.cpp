#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
Given a number of integers, combine them so it would create the largest number.
Example:
Input: [17, 7, 2, 45, 72]
Output: 77245217
*/

/* QUESTION: overflow? Should we use and return strings or is there a bound on size of output?
Will assume no reasonable (2^63) upper bound on output: return string */

/* APPROACH 1: Custom compare function for integers. Given a and b, we can combine as either ab or
ba. We want the bigger between "ab" and "ba". If "ab" is bigger, then we say a > b. According to this
compare, we sort in decreasing order (largest first) and append the resulting vector.
O(N log N) time, O(N) space */
int myCompare(string a, string b) {
    return (a+b).compare(b+a);
}
void sort(vector<string> &arr, int l, int r) {
    if (l <= r) {
        int m = l;
        string splitter = arr[r];
        for (int i = l; i < r; i++) {
            if (myCompare(arr[i], splitter) > 0) {
                string temp = arr[i];
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
string findBiggestNumber(vector<int> &nums) {
    int n = nums.size();
    vector<string> strNums;
    for (int i = 0; i < n; i++) strNums.push_back(to_string(nums[i]));
    sort(strNums, 0, n-1);
    if (strNums[0] == "0") return "0";
    string ans = "";
    for (int i = 0; i < n; i++) ans += strNums[i];
    return ans;
}

int main(int argc, char **argv) {
    vector<int> nums = {17, 7, 2, 45, 72};
    std::cout << findBiggestNumber(nums) << '\n';
    return 0;
}
