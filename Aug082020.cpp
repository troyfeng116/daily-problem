#include <iostream>
#include <vector>
using namespace std;

/*
Given a list of numbers with only 3 unique numbers (1, 2, 3), sort the list in O(n) time.

Example 1:
Input: [3, 3, 2, 1, 3, 2, 1]
Output: [1, 1, 2, 2, 3, 3, 3]

Challenge: Try sorting the list using constant space.
*/

void sort(vector<int> *list) {
	/* From 0->l is all 1s. From l->m is all 2s. From m->r is unsorted. From r->end is all 3s. */
	int l = 0;
	int m = 0;
	int r = (*list).size()-1;
	while (m <= r) {
		if ((*list)[m] == 1) {
			(*list)[m] = (*list)[l];
			(*list)[l] = 1;
			l++;
			m++;
		}
		else if ((*list)[m] == 2) m++;
		else {
			(*list)[m] = (*list)[r];
			(*list)[r] = 3;
			r--;
		}
	}
}

int main(int argc, char **argv) {
	vector<int> test = {3, 3, 2, 3, 2,2,2,2,2,2,2,2,1,3};
	for (int i = 0; i < test.size(); i++) std::cout << test[i] << " ";
	std::cout << '\n';
	sort(&test);
	for (int i = 0; i < test.size(); i++) std::cout << test[i] << " ";
	std::cout << '\n';
	return 0;
}
