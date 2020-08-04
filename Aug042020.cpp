/*
A palindrome is a sequence of characters that reads the same backwards and forwards. Given a string, s,
find the longest palindromic substring in s.

Example:
Input: "banana"
Output: "anana"

Input: "million"
Output: "illi"
*/

#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
NAIVE: Generate all substrings, check if palindrome. O(N^3)
BETTER1: Check 2*N-1 centers. O(N^2)
BETTER2: DP?
BEST: Manacher's.
*/

string longestPalindrome1(string s) {
	int n = s.length();
	string ans = "";
	int ansLen = 0;
	for (int center = 0; center < 2*n; center++) {
		int l = center/2;
		int r = center%2==0? center/2 : center/2+1;
		while (l > 0 && r < n-1 && s.at(l-1) == s.at(r+1)) {
			l--;
			r++;
		}
		if (r-l+1 > ansLen) {
			ans = s.substr(l,r-l+1);
			ansLen = r-l+1;
		}
	}
	return ans;
}

string longestPalindrome2(string s) {
	int n = s.length();
	/* dp[i][j] is true if s[i,j] is palindrome. */
	vector<vector<bool>> dp;
	for (int i = 0; i < n; i++) {
		vector<bool> row;
		for (int j = 0; j < n; j++) {
			if (i == j || i == j-1) row.push_back(true);
			else row.push_back(false);
		}
		dp.push_back(row);
	}
	int l = 0;
	int r = 0;
	for (int len = 1; len < n; len++) {
		for (int i = 0; i < n-len; i++) {
			int j = i+len;
			if (s.at(i) == s.at(j) && dp[i+1][j-1]) {
				std::cout << i << " " << j << "\n";
				dp[i][j] = true;
				if (j-i+1 > r-l+1) {
					l=i;
					r=j;
				}
			}
		}
	}
	return s.substr(l,r-l+1);
}

/* Manacher's algorithm */
string longestPalindrome3(string s) {
	int n = s.length();
	/* Add # between all chars in s to deal with even length palindromes */
	string str = "^#";
	for (int i = 0; i < n; i++) {
		str += s.at(i);
		str += '#';
	}
	str += '$';
	vector<int> lp;
	for (int i = 0; i < 2*n+3; i++) lp.push_back(0);
	/* Initialize c, i, r */
	int c = 0, r = 0;
	int ansC = 0, ansLen = 0;
	for (int i = 1; i < 2*n+2; i++) {
		int mirror = 2*c-i;
		if (i < r) {
			lp[i] = min(lp[mirror], r-i);
		}

		while (str.at(i+(1+lp[i])) == str.at(i-(1+lp[i]))) {
			lp[i]++;
		}

		if (i+lp[i] > r) {
			c = i;
			r = i + lp[i];
		}
		
		if (lp[i] > ansLen) {
			ansC = i;
			ansLen = lp[i];
		}
	}
	return s.substr((ansC-ansLen)/2, (ansC+ansLen)/2-1);

}

int main(int argc, char** argv) {
	string s1 = "banana";
	string s2 = "million";
	std::cout << longestPalindrome1(s1)+" "+longestPalindrome1(s2)+"\n";
	std::cout << longestPalindrome2(s1)+" "+longestPalindrome2(s2)+"\n";
	std::cout << longestPalindrome3(s1)+" "+longestPalindrome3(s2)+"\n";
	return 0;
}
