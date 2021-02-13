#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/*
A majority element is an element that appears more than half the time. Given a list with a majority element,
find the majority element.

ex. [3, 5, 3, 3, 2, 4, 3] => 3
*/

/* APPROACH 1: There can only be one majority element. Bucket sort and return element whose frequency 
exceeds half of list size. O(N) time and space */
int findMajorityElement(vector<int> list) {
    int n = list.size();
    unordered_map<int, int> map;
    for (int i = 0; i < n; i++) {
        if (map.find(list[i]) == map.end()) map[list[i]] = 0;
        map[list[i]]++;
    }
    for (int i = 0; i < n; i++) {
        if (map[list[i]] > n / 2) return list[i];
    }
    cout << "Bad input: no majority element\n";
    return -1;
}

/* APPROACH 2: Boyer-Moore voting algorithm. O(N) */
int findMajorityElement2(vector<int> list) {
    int majority = list[0];
    int count = 1;
    for (int i = 1; i < list.size(); i++) {
        if (list[i] == majority) {
            count++;
        } else count--;
        if (count == 0) {
            majority = list[i];
            count = 1;
        }
    }
    // No need to verify that majority is the majority element by input assumption
    return majority;
}

int main(int argc, char **argv) {
    vector<int> list = {3, 5, 3, 3, 2, 4, 3};
    cout << "APPROACH 1 TESTING: " << findMajorityElement(list) << '\n';
    cout << "APPROACH 2 TESTING: " << findMajorityElement2(list) << '\n';
    return 0;
}
