#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

/*
Given a number n, find the least number of squares needed to sum up to the number.
*/

/* APPROACH 1: pretty much least ways to make change problem. Coin values are squares,
change is n. DP: O(n) time + space */
int leastSquares(int n) {
    vector<int> dp(n+1, INT_MAX);
    dp[0] = 0;
    for (int target = 1; target <= n; target++) {
        for (int s = 1; s*s <= target; s++) {
            dp[target] = min(dp[target - s*s] + 1, dp[target]);
        }
    }
    return dp[n];
}

/* APPROACH 2: Lagrange's four square theorem. Check if n can be written as sum of 1, 2,
and 3 squares, else return 4. This becomes a bunch of 2-sum problems.
O(n) time, O(sqrt(n)) space */
int leastSquares2(int n) {
    int floorSqrt = sqrt(n);
    if (floorSqrt * floorSqrt == n) return 1;
    unordered_set<int> squareSet;
    for (int i = 1; i*i <= n; i++) {
        squareSet.insert(i * i);
    }
    unordered_set<int> squareDiffSet;
    for (int i = 1; i*i <= n; i++) {
        if (squareSet.count(n - i*i) > 0) return 2;
        squareDiffSet.insert(n - i*i);
    }
    for (auto it = squareDiffSet.begin(); it != squareDiffSet.end(); it++) {
        for (int i = 1; i*i <= *it; i++) {
            if (squareSet.count(*it - i*i) > 0) return 3;
        }
    }
    return 4;
}

int main(int argc, char **argv) {
    int n = 131;
    std::cout << "APPROACH 1: " << leastSquares(n) << '\n';
    std::cout << "APPROACH 2: " << leastSquares2(n) << '\n';
    return 0;
}
