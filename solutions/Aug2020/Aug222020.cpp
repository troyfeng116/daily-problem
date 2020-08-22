#include <iostream>
using namespace std;

/*
You are given 2 integers n and m representing an n by m grid, determine the number of ways you can 
get from the top-left to the bottom-right of the matrix y going only right or down.

Example:
n = 2, m = 2

This should return 2, since the only possible routes are:
Right, down
Down, right.
*/

/*
APPROACH 1: DP. Let dp[i][j] be the total number of ways to get to grid[i][j]. Then
dp[i][j] = dp[i-1][j] + dp[i][j-1]. Runs in O(M*N) time and space.
*/
int numPaths1(int m, int n) {
	/* Initialize dp. */
	int **dp = (int**) malloc(sizeof(int*) * m);
	for (int i = 0; i < m; i++) {
		dp[i] = (int*) malloc(sizeof(int) * n);
	}
	for (int i = 0; i < m; i++) dp[i][0] = 1;
	for (int j = 0; j < n; j++) dp[0][j] = 1;
	for (int i = 1; i < m; i++) {
		for (int j = 1; j < n; j++) {
			dp[i][j] = dp[i-1][j] + dp[i][j-1];
		}
	}
	int ans = dp[m-1][n-1];
	for (int i = 0; i < m; i++) {
		free(dp[i]);
	}
	free(dp);
	return ans;
}

/*
APPROACH 2: Combinatorics. Problem equivalent to how many ways are there to arrange (m-1) downs
or (n-1) rights in (m+n-2) steps: any path must take (m+n-2) total steps, with some sequence of
(m-1) downs and (n-1) rights. O(min(m,n)) for choose function, constant space.
*/
int choose(int n, int k) {
	long ans = 1;
	for (int i = max(k,n-k)+1; i <= n; i++) {
		ans *= i;
	}
	for (int i = 1; i <= min(k,n-k); i++) {
		ans /= i;
	}
	return (int) ans;
}
int numPaths2(int m, int n) {
	return choose(m+n-2, m-1);
}

int main(int argc, char **argv) {
	std::cout << numPaths1(15,12) << '\n';
	std::cout << numPaths2(15,12) << '\n';
	return 0;
}
