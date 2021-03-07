#include <iostream>
#include <vector>
using namespace std;

/*
Given an array of size n, and all values in the array are in the range 1 to n, find all the duplicates.

ex. [4, 3, 2, 7, 8, 2, 3, 1] -> [2, 3]
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
    cout << arr.back() << "]\n";
}

/* APPROACH 1: reuse input arr as hashmap by marking "found" by adding n to that index. Since values
are from 1 to n, only spots >= 2n + 1 are duplicated. O(N) time, O(1) space */
vector<int> findDuplicates(vector<int> arr) {
    int n = arr.size();
    for (int i = 0; i < arr.size(); i++) {
        arr[(arr[i] % n) - 1] += n;
    }
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        if (arr[i] >= 2 * n + 1) ans.push_back(i + 1);
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<int> test = {4, 3, 2, 7, 8, 2, 3, 1};
    print(findDuplicates(test));
    return 0;
}
