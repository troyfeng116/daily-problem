#include <iostream>
#include <vector>
using namespace std;

/*
There are n people lined up, and each have a height represented as an integer. A murder has 
happened right in front of them, and only people who are taller than everyone in front of them 
are able to see what has happened. How many witnesses are there?

Example:
Input: [3, 6, 3, 4, 1]  
Output: 3
Explanation: Only [6, 4, 1] were able to see in front of them.
 #
 #
 # #
####
####
#####
36341                                 x (murder scene)
*/

/* APPROACH 1: just traverse array in reverse order than track max to the right of curPos. */
int numWitnesses(vector<int> heights) {
	int maxToRight = INT_MIN;
	int result = 0;
	for (int i = heights.size()-1; i >= 0; i--) {
		if (heights[i] > maxToRight) {
			maxToRight = heights[i];
			result++;
		}
	}
	return result;
}

int main(int argc, char **argv) {
	vector<int> test;
	test.push_back(3);
	test.push_back(6);
	test.push_back(3);
	test.push_back(4);
	test.push_back(1);
	std::cout << numWitnesses(test) << '\n';
	return 0;
}
