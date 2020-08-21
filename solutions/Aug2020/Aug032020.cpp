/*
Given a string, find the length of the longest substring without repeating characters.
*/

#include <iostream>
#include <string>
using namespace std;

/*
APPROACH 1: Two pointers. At any moment, say between l and r are all unique. We need to track last
occurrence of each character that appears. Say l is at 1, there is a 'c' at 5, and r is at 7. When
we shift r to 8, we find another 'c.' Now, we have to shift l to 6 before continuing.
*/
string solution1(string str) {
	int table[256];
	for (int i = 0; i < 256; i++) table[i] = -1;
	int l = 0;
	table[(int) str.at(0)] = 0;
	string ans = str.substr(0,1);
	int ansLen = 1;
	for (int r = 1; r < str.length(); r++) {
		if (table[(int) str.at(r)] >= 0) {
			int m = table[(int) str.at(r)];
			for (int i = l; i <= m; i++) {
				table[(int) str.at(i)] = -1;
			}
			l = m+1;
		}
		table[(int) str.at(r)] = r;
		if (r-l+1 > ansLen) {
			ansLen = r-l+1;
			ans = str.substr(l,ansLen);
		}
	}
	return ans;
}

int main(int argc, char** argv) {
	string str = "pwwkew";
	std::cout << solution1(str) << '\n';
	return 0;
}
