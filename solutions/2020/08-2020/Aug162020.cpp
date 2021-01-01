#include <iostream>
#include <vector>
#include <unordered_set>
#include <math.h>
using namespace std;

/*
Given a list of numbers, find if there exists a pythagorean triplet in that list. A pythagorean triplet 
is 3 variables a, b, c where a^2 + b^2 = c^2

Example:
Input: [3, 5, 12, 5, 13]
Output: True

Here, 5^2 + 12^2 = 13^2.
*/

/* 
QUESTION: 
-does the triple have to be ordered in the list (i.e. a subsequence)? I will assume no.
-are the numbers in the list guaranteed to be positive integers? I will assume yes (Pythagorean triples 
are defined to be integers)
*/

/*
HASHING APPROACH
We can take O(N) to hash the squares of each element in the list in a set. Then, since all integer Pythagorean
triples have no two sides equal, we can just loop over all (a,b) pairs and look up if a^2 + b^2 is in the set.
O(N^2), O(N) space
*/
bool hasPythagTriple1(vector<int> list) {
	unordered_set<int> table;
	for (int i = 0; i < list.size(); i++) table.insert(list[i]*list[i]);
	for (int i = 0; i < list.size(); i++) {
		for (int j = i+1; j < list.size(); j++) {
			int a = list[i];
			int b = list[j];
			if (table.count(a*a+b*b) > 0) {
				std::cout <<"FOUND: "<<a<<' '<<b<<' '<<sqrt(a*a+b*b)<<'\n';
				return true;
			}
		}
	}
	return false;
}

/*
TWO-POINTERS APPROACH
If we first map each element to its square and then sort (O(N log(N)) time), we can use a two pointers
approach. Let c be the last element, a be the first, and b be the element right before c. Then we need
a+b equals some target. If a+b > c, decrement b (to make a+b smaller). If a+b < c, increment a. If a >= b,
return decrement c and restart the loop. If a+b == c, return true.
O(N^2) time, O(1) extra space.
*/
void sort(vector<int> *list, int l, int r) {
	if (l >= r) return;
	int splitter = (*list)[r];
	int m = l;
	for (int i = l; i < r; i++) {
		if ((*list)[i] < splitter) {
			int temp = (*list)[m];
			(*list)[m] = (*list)[i];
			(*list)[i] = temp;
			m++;
		}
	}
	(*list)[r] = (*list)[m];
	(*list)[m] = splitter;
	sort(list, l, m-1);
	sort(list, m+1, r);
}
bool hasPythagTriple2(vector<int> list) {
	sort(&list, 0, list.size()-1);
	for (int cPointer = list.size()-1; cPointer >= 0; cPointer--) {
		int c = list[cPointer];
		int aPointer = 0;
		int bPointer = cPointer-1;
		while (aPointer < bPointer) {
			int a = list[aPointer];
			int b = list[bPointer];
			if (a*a+b*b < c*c) aPointer++;
			else if (a*a+b*b > c*c) bPointer--;
			else {
				std::cout <<"FOUND: "<<a<<' '<<b<<' '<<c<<'\n';
				return true;
			}
		}
	}
	return false;
}

int main(int argc, char **argv) {
	vector<int> list;
	list.push_back(12);
	list.push_back(4);
	list.push_back(12);
	list.push_back(5);
	list.push_back(3);
	std::cout << hasPythagTriple1(list) << '\n';
	std::cout << hasPythagTriple2(list) << '\n';
	return 0;
}
