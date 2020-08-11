#include <iostream>
#include <vector>
using namespace std;

/*
You are given an array of integers in an arbitrary order. Return whether or not it is possible to make 
the array non-decreasing by modifying at most 1 element to any value.

We define an array is non-decreasing if array[i] <= array[i + 1] holds for every i (1 <= i < n).

Example:

[13, 4, 7] should return true, since we can modify 13 to any value 4 or less, to make it non-decreasing.

[13, 4, 1] however, should return false, since there is no way to modify just one element to make the 
array non-decreasing.

Can you find a solution in O(n) time?
*/

/*
Loop through array, if we find a spot where the array decreases, that must be the 1) the only spot and 2)
the next element must be >= the element before the increase.
*/

bool canModifyOne(vector<int> arr) {
	int i = 0;
	bool foundDecr = false;
	while (i < arr.size()-1) {
		if (arr[i] > arr[i+1]) {
			if (!foundDecr) {
				foundDecr = true;
				if (i == arr.size()-2) return true;
				// CASE 1: if arr[i] > arr[i+2] >= arr[i+1], need to sandwich a[i] between arr[i-1] and arr[i+1].
				if ((arr[i] > arr[i+2] && arr[i+2] >= arr[i+1])) {
					if (i == 0 || arr[i-1] <= arr[i+1]) {
						i += 2;
						continue;
					}
					return false;
				}
				// CASE 2: If arr[i+2] >= arr[i], we have to sandwich arr[i+1] between arr[i] and arr[i+2].
				if (arr[i+2] >= arr[i]) {
					i += 2;
					continue;
				}
				else return false;
			}
			else return false;
		}
		i++;
	}
	return true;
}


int main(int argc, char **argv) {
	vector<int> test;
	for (int i = 1; i < 10; i++) test.push_back(i);
	std::cout << canModifyOne(test) << '\n';
	test[0] = 2;
	test[1] = 1;
	std::cout << canModifyOne(test) << '\n';
	test[8] = 0;
	std::cout << canModifyOne(test) << '\n';
	vector<int> test2;
	test2.push_back(13);
	test2.push_back(7);
	test2.push_back(1);
	std::cout << canModifyOne(test2) << '\n';
	return 0;
}
