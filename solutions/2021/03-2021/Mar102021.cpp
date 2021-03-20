#include <iostream>
#include <vector>
using namespace std;

/*
Given 2 integers n and m representing an n by m grid, determine the number of ways
you can get from the top-left to the bottom-right of an n x m matrix going only right or down.

ex.
n = 2, m = 2

=> 2
The only possible routes are:
right -> down
down -> right
*/

/* APPROACH 1: DP. If dp[i][j] = number of ways to get to mat(i,j), then 
dp[i][j] = dp[i - 1][j] + dp[i][j - 1]. O(M * N) */
int numWaysToTraverseMatrix(int m, int n) {
    vector<vector<int> > dp(m, vector<int>(n, 0));
    for (int r = 0; r < m; r++) {
        dp[r][0] = 1;
    }
    for (int c = 0; c < n; c++) {
        dp[0][c] = 1;
    }
    for (int r = 1; r < m; r++) {
        for (int c = 1; c < n; c++) {
            dp[r][c] = dp[r - 1][c] + dp[r][c - 1];
        }
    }
    return dp[m - 1][n - 1];
}

/* APPROACH 2: combinatorics. Since there are (m - 1) + (n - 1) moves in total, and m - 1 of
those moves must be down, we can return the number of ways to arrange (m - 1) D moves in
a sequence of (m + n - 2) total moves, or {m + n - 2} CHOOSE {m - 1}. O(M + N) */
int choose(int n, int r) {
    int k = min(r, n - r);
    int denominator = 1;
    for (int i = 2; i <= k; i++) denominator *= i;
    int numerator = 1;
    for (int i = n - k + 1; i <= n; i++) numerator *= i;
    return numerator / denominator;
}
int numWaysToTraverseMatrix2(int m, int n) {
    return choose(m + n - 2, m - 1);
}

int main(int argc, char **argv) {
    int m = 5, n = 8;
    cout << "APPROACH 1 TESTING: " << numWaysToTraverseMatrix(m, n) << '\n';
    cout << "APPROACH 2 TESTING: " << numWaysToTraverseMatrix2(m, n) << '\n';
    return 0;
}
