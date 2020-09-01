#include <iostream>
using namespace std;

/*
You are given an array of integers. Return the largest product that can be made by multiplying 
any 3 integers in the array.

Example:

[-4, -4, 2, 8] should return 128 as the largest product can be made by multiplying -4 * -4 * 8 
= 128.
*/

/* QUESTIONS: Guaranteed |arr|>=3? Assume yes */

/* APPROACH 1: Casework. We need to store the 3 largest and 2 smallest numbers: can be done in
one pass and constant space (5 ints).
CASE 1: No negatives (smallest is positive). Return product of 3 largest.
CASE 2: 1 negative (second smallest is positive). Return product of 3 largest.
CASE 3: 2 negatives (third smallest is positive). Return max of: 3 largest or 2smallest*largest.
CASE 4: 3+ negatives. Same as case 3.
CASE 5: No positives. Same as case 1.
One pass to find 3 largest and 3 smallest, constant time return. O(N) */

int largestProduct(int *arr, int n) {
	/* largest, 2nd largest, 3rd largest */
	int max = INT_MIN, secondMax = INT_MIN, thirdMax = INT_MIN;
	/* smallest, 2nd smallest */
	int min = INT_MAX, secondMin = INT_MAX;
	for (int i = 0; i < n; i++) {
		if (arr[i] >= thirdMax) {
			thirdMax = arr[i];
			if (thirdMax >= secondMax) {
				int temp = secondMax;
				secondMax = thirdMax;
				thirdMax = temp;
			}
			if (secondMax >= max) {
				int temp = max;
				max = secondMax;
				secondMax = temp;
			}
		}
		if (arr[i] <= secondMin) {
			secondMin = arr[i];
			if (secondMin <= min) {
				int temp = min;
				min = secondMin;
				secondMin = temp;
			}
		}
	}
	/* CASE 1/5 */
	if (min >= 0 || max <= 0) return (max * secondMax * thirdMax);
	/* CASE 2 */
	if (secondMin >= 0) return (max * secondMax * thirdMax);
	/* CASE 3/4 */
	return std::max((max * secondMax * thirdMax), (min * secondMin * max));
}

int main(int argc, char **argv) {
	int n = 4;
	int *test = new int[n];
	test[0] = -4; test[1] = -4; test[2] = 2; test[3] = 8;
	std::cout << largestProduct(test, 4) << '\n';
	return 0;
}
