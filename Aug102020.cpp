#include <iostream>
using namespace std;

/*
Given a list of numbers, where every number shows up twice except for one number, find that one number.

Example:
Input: [4, 3, 2, 4, 1, 3, 2]
Output: 1

Challenge: Find a way to do this using O(1) memory.
*/

/*
One approach is to Hash the number of occurrences. Best approach is to XOR all the entries. Because XOR
is commutative, and because x^x = 0 for all x, this will leave us with the answer.
*/

int findUnique(int *arr, int len) {
	int XOR = 0;
	for (int i = 0; i < len; i++) {
		XOR ^= arr[i];
	}
	return XOR;
}

int main(int argc, char **argv) {
	int arr[] = {4, 3, 2, 4, 100, 3, 2};
	std::cout << findUnique(arr,7) << '\n';
	return 0;
}
