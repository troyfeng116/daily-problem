#include <iostream>
#include <vector>
using namespace std;
/*
Given an array of n positive integers and a positive integer s, find the minimal length of a 
contiguous subarray of which the sum ≥ s. If there isn't one, return 0 instead.

Example:
Input: s = 7, nums = [2,3,1,2,4,3]
Output: 2
Explanation: the subarray [4,3] has the minimal length under the problem constraint.
*/

/*
I think sliding window could work. Keep l and r pointers. If sum<s, extend r. Else, remove at l.
*/
int minContToSum(vector<int> arr, int s) {
	int sum = 0;
	int l = 0;
	int r = 0;
	/* Initialize l and r to be the first window such that sum[l,r] >= s, initialize min to l-r. */
	while (r < arr.size() && sum < s) {
		sum += arr[r];
		r++;
	}
	if (r >= arr.size()) return 0;
	int min = r-l;
	/* Slide the window, update min as we go. */
	while (r < arr.size()) {
		if (sum >= s) {
			sum -= arr[l];
			l++;
		}
		else {
			sum += arr[r];
			r++;
		}
		if (sum >= s && r-l < min) min = r-l;
	}
	return min;
}

int main(int argc, char **argv) {
	vector<int> arr;
	arr.push_back(2);
	arr.push_back(3);
	arr.push_back(1);
	arr.push_back(2);
	arr.push_back(1);
	arr.push_back(3);
	arr.push_back(1);
	std::cout << minContToSum(arr,70) << '\n';
	return 0;
}
