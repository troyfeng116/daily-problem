#include <iostream>
#include <vector>
using namespace std;

/*
Given a list of positive numbers, find the largest possible subset sum such that no elements are
adjacent numbers of each other.

ex.
list = [2, 1, 2, 7, 3] -> 9. Indices 0 and 3 are non-adjacent and 2 + 7 is largest sum.
*/

/* APPROACH 1: Since list is positive, max numbers to skip over is 2, and the only two starting
points are indices 0 and 1. Run recursion from each starting point. Exponential time */
int dfs(vector<int> list, int i, int cSum) {
    if (i >= list.size()) return cSum;
    return max(dfs(list, i + 2, cSum + list[i]), dfs(list, i + 3, cSum + list[i]));
}
int maxNonAdjacentSum(vector<int> list) {
    return max(dfs(list, 0, 0), dfs(list, 1, 0));
}

/* APPROACH 2: DP. Let dp[i] = max non-adj subset sum of list[0, i]. Then
dp[i] = max(dp[i - 1], dp[i - 2] + list[i]).
O(N) time and space */
int maxNonAdjacentSum2(vector<int> list) {
    int n = list.size();
    if (n == 0) return 0;
    if (n == 1) return list[0];
    if (n == 2) return max(list[0], list[1]);
    vector<int> dp(n, 0);
    dp[0] = list[0];
    dp[1] = max(list[0], list[1]);
    for (int i = 2; i < n; i++) {
        dp[i] = max(dp[i - 1], dp[i - 2] + list[i]);
    }
    return dp[n - 1];
}

/* APPROACH 3: We only ever need the max values up to the indices 1 and 2 back from i. O(N) time, O(1) space */
int maxNonAdjacentSum3(vector<int> list) {
    int n = list.size();
    if (n == 0) return 0;
    if (n == 1) return list[0];
    int prev = list[0];
    int cur = max(list[0], list[1]);
    int ans = max(cur, prev);
    for (int i = 2; i < list.size(); i++) {
        ans = max(cur, prev + list[i]);
        prev = cur;
        cur = ans;
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<int> list = {2, 1, 2, 7, 3};
    cout << "APPROACH 1 TESTING: " << maxNonAdjacentSum(list) << '\n';
    cout << "APPROACH 2 TESTING: " << maxNonAdjacentSum2(list) << '\n';
    cout << "APPROACH 3 TESTING: " << maxNonAdjacentSum3(list) << '\n';
    return 0;
}
