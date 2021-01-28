#include <iostream>
#include <vector>
#include <unordered_set>
using namespace std;

/*
Given 3 sorted lists, find the intersection of those 3 lists.

ex. intersection([1, 2, 3, 4], [2, 4, 6, 8], [3, 4, 5]) => [4]
*/

/*
QUESTION: duplicates? i.e. if 4 appears three times in all three lists, return [4, 4, 4] or just [4]?
Will assume return one instance of each intersection for simplicity
*/

void print(vector<int> arr) {
    if (arr.size() == 0) {
        cout << "[]\n";
        return;
    }
    cout << "[";
    for (int i = 0; i < arr.size() - 1; i++) {
        cout << arr[i] << ", ";
    }
    cout << arr[arr.size() - 1] << "]\n";
}

/* APPROACH 1: iterate through each list, adding seen numbers to a set. Narrow down the set for
each list. Basically find intersection of first two lists, then find intersection of that intersection
with third list. O(N1 + N2 + N3) time, O(N1 + N2) space */
vector<int> findIntersection(vector<int> l1, vector<int> l2, vector<int> l3) {
    unordered_set<int> set;
    for (int i = 0; i < l1.size(); i++) {
        set.insert(l1[i]);
    }
    unordered_set<int> set2;
    for (int i = 0; i < l2.size(); i++) {
        if (set.find(l2[i]) != set.end()) set2.insert(l2[i]);
    }
    vector<int> ans;
    for (int i = 0; i < l3.size(); i++) {
        if (set2.find(l3[i]) != set2.end()) {
            set2.erase(l3[i]);
            ans.push_back(l3[i]);
        }
    }
    return ans;
}

/* APPROACH 2: One pointer for each list, increment either of the smaller pointers.
O(N1 + N2 + N3) time */
vector<int> findIntersection2(vector<int> l1, vector<int> l2, vector<int> l3) {
    int n1 = l1.size(), n2 = l2.size(), n3 = l3.size();
    unordered_set<int> set;
    int i = 0, j = 0, k = 0;
    while (i < n1 && j < n2 && k < n3) {
        if (l1[i] == l2[j] && l2[j] == l3[k]) {
            set.insert(l1[i]);
            i++;
            j++;
            k++;
        } else if (l1[i] < l2[j]) {
            i++;
        } else if (l2[j] < l3[k]) {
            j++;
        } else k++;
    }
    vector<int> ans;
    for (auto it = set.begin(); it != set.end(); it++) {
        ans.push_back(*it);
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<int> l1 = {1, 2, 3, 4};
    vector<int> l2 = {1, 2, 3, 4, 6, 8};
    vector<int> l3 = {3, 4, 5};

    cout << "APPROACH 1: ";
    print(findIntersection(l1, l2, l3));

    cout << "APPROACH 2: ";
    print(findIntersection2(l1, l2, l3));

    return 0;
}