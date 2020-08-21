#include <iostream>
#include <vector>
#include <set>
using namespace std;

/*
You are given a list of numbers, and a target number k. Return whether or not there are two numbers in
the list that add up to k.

Example:
Given [4, 7, 1 , -3, 2] and k = 5,
return true since 4 + 1 = 5.

Try to do it in a single pass of the list.
*/

/* Use hash table to store found elements, and search for complements as we go. */
bool hasTwoSum(vector<int> list, int k) {
	set<int> table;
	for (int i = 0; i < list.size(); i++) {
		if (table.count(k - list[i])) {
			return true;
		}
		table.insert(list[i]);
	}
	return false;
}

int main(int argc, char **argv) {
	vector<int> list = {4,7,1,-3,2};
	std::cout << hasTwoSum(list, 3) << '\n';
	return 0;
}
