#include <iostream>
#include <vector>
using namespace std;

/*
Given a list of unique numbers, generate all possible subsets without duplicates. This includes
the empty set as well.

ex.
list = [1, 2, 3] => [[], [1], [2], [3], [1,2], [1,3], [2,3], [1,2,3]]
*/

void printArr(vector<int> arr) {
    if (arr.size() == 0) {
        cout << "[]\n";
        return;
    }
    cout << "[";
    for (int i = 0; i < arr.size() - 1; i++) {
        cout << arr[i] << ", ";
    }
    cout << arr.back() << "]\n";
}

void printListOfArr(vector<vector<int> > list) {
    for (int i = 0; i < list.size(); i++) {
        printArr(list[i]);
    }
}

/* APPROACH 1: Bits (2^n subsets). O(n * 2^n) */
vector<int> bitsToList(vector<int> list, int bits) {
    vector<int> ans;
    for (int i = 0; i < list.size(); i++) {
        if ((bits & 1) == 1) ans.push_back(list[i]);
        bits = bits >> 1;
    }
    return ans;
}
vector<vector<int> > generateSubsets(vector<int> list) {
    vector<vector<int> > ans;
    for (int bits = 0; bits < pow(2, list.size()); bits++) {
        ans.push_back(bitsToList(list, bits));
    }
    return ans;
}

/* APPROACH 2: Recursion + backtracking. O(2^n) */
void dfs(vector<int> list, int index, vector<int> &curList, vector<vector<int> > &subsets) {
    if (index >= list.size()) {
        vector<int> newList(curList);
        subsets.push_back(newList);
        return;
    }
    dfs(list, index + 1, curList, subsets);
    curList.push_back(list[index]);
    dfs(list, index + 1, curList, subsets);
    curList.pop_back();
}
vector<vector<int> > generateSubsets2(vector<int> list) {
    vector<vector<int> > subsets;
    vector<int> curList;
    dfs(list, 0, curList, subsets);
    return subsets;
}

int main(int argc, char **argv) {
    vector<int> test = {1, 2, 3};

    cout << "APPROACH 1 TESTING:\n";
    printListOfArr(generateSubsets(test));

    cout << "APPROACH 2 TESTING:\n";
    printListOfArr(generateSubsets2(test));
    return 0;
}
