#include <iostream>
#include <vector>
using namespace std;

/*
Given a list of possible coins in cents, and an amount (in cents) n, return the minimum number of
coins needed to create the amount n. If it is not possible to create the amount using the given 
coin denomination, return None.
*/

/* APPROACH 1: DP. dp[k] = minimum coins needed to make k change. O(n * #coins) time, O(n) space */
int minCoinsForChange(vector<int> coins, int n) {
    vector<int> dp(n+1, INT_MAX);
    dp[0] = 0;
    for (int k = 1; k <= n; k++) {
        for (int coin : coins) {
            if (k - coin >= 0 && dp[k-coin] != INT_MAX) dp[k] = min(dp[k], dp[k-coin] + 1);
        }
    }
    return dp[n];
}

int main(int argc, char **argv) {
    vector<int> coins = {1, 5, 10, 25};
    int n = 36;
    std::cout << minCoinsForChange(coins, n) << '\n';
    return 0;
}
