#include <iostream>
#include <string>
using namespace std;

/*
Given two strings, determine the edit distance between them. The edit distance is defined as the minimum 
number of edits (insertion, deletion, or substitution) needed to change one string to the other.

For example, "biting" and "sitting" have an edit distance of 2 (substitute b for s, and insert a t).
*/

/*
APPROACH 1: If we find longest common subsequence, we need to substitute for letters not in LCS and insert
the rest.
EDIT: This does not work for several cases (where subsequences don't line up for strings of equal length,
for example "intention" and "execution", LCS is 5 because of 'e', but the e's don't line up.)
*/
int lcs(string s1, string s2) {
	int n = s1.length();
	int m = s2.length();
	int table[n+1][m+1];
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (i == 0 || j == 0) table[i][j] = 0;
			else if (s1.at(i-1) == s2.at(j-1)) {
				table[i][j] = 1+table[i-1][j-1];
			}
			else table[i][j] = max(table[i-1][j], table[i][j-1]);
		}
	}
	return table[n][m];
}
int editDistance1(string s1, string s2) {
	int n = s1.length();
	int m = s2.length();
	int common = lcs(s1,s2);
	return abs(m-n) + min(m,n)-common;
}

/*
APPROACH 2: DP. Let dp[i][j] denote edit distance between s1[0,i) and s2[0,j).
If s1[i-1]==s2[j-1], dp[i][j] = dp[i-1][j-1].
Else, dp[i][j] = min(dp[i-1][j], dp[i][j-1], dp[i-1][j-1])+1.
Base cases: dp[0][j] = j and dp[i][0] = i.
O(MN).
*/
int editDistance2(string s1, string s2) {
	int n = s1.length();
	int m = s2.length();
	int dp[n+1][m+1];
	for (int i = 0; i <= n; i++) {
		for (int j = 0; j <= m; j++) {
			if (i == 0) dp[i][j] = j;
			else if (j == 0) dp[i][j] = i;
			else if (s1.at(i-1) == s2.at(j-1)) {
				dp[i][j] = dp[i-1][j-1];
			}
			else {
				dp[i][j] = min(dp[i-1][j], min(dp[i][j-1], dp[i-1][j-1]))+1;
			}
		}
	}
	return dp[n][m];
}

int main(int argc, char **argv) {
	string s1 = "sitting";
	string s2 = "biting";
	std::cout << editDistance2(s1,s2) << '\n';
	return 0;
}
