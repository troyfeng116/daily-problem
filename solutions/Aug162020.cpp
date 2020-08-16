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
-are the numbers in the list guaranteed to be integers? I will assume yes (Pythagorean triples are defined
to be integers)
*/

/*
We can take O(N) to add the squares of each element in the list to a set. Then, since all integer Pythagorean
triples have no two sides equal, we can just loop over all (a,b) pairs and look up if a^2 + b^2 is in the set.
O(N^2), O(N) space
*/
bool hasPythagTriple(vector<int> list) {
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

int main(int argc, char **argv) {
	vector<int> list;
	list.push_back(12);
	list.push_back(5);
	list.push_back(12);
	list.push_back(5);
	list.push_back(13);
	std::cout << hasPythagTriple(list) << '\n';
	return 0;
}
