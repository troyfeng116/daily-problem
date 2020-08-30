#include <iostream>
using namespace std;

/*
Given an array nums, write a function to move all 0's to the end of it while maintaining the 
relative order of the non-zero elements.

Example:
Input: [0,1,0,3,12]
Output: [1,3,12,0,0]
You must do this in-place without making a copy of the array.
Minimize the total number of operations.
*/

/*
APPROACH 1: The typical partitioning is not stable (doesn't preserve original relative order).
One way is: if zero found, sift all elements left and replace last element with zero. This runs
in O(N^2) time: O(N) pass, and O(N) to shift on each pass.
*/
void moveZeroes(int *arr, int n) {
	int l = 0;
	int r = n-1;
	while (l <= r) {
		if (arr[l] == 0) {
			for (int i = l; i < r; i++) {
				arr[i] = arr[i+1];
			}
			arr[r] = 0;
			r--;
		}
		else l++;
	}
}

int main(int argc, char **argv) {
	int n = 5;
	int *arr = new int[n];
	arr[0] = 0;
	arr[1] = 1;
	arr[2] = 0;
	arr[3] = 3;
	arr[4] = 12;
	moveZeroes(arr, n);
	for (int i = 0; i < n; i++) {
		std::cout << arr[i] << " \n";
	}
	return 0;
}
