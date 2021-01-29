#include <iostream>
#include <vector>
using namespace std;

/*
Pascal's Triangle is a triangle where all numbers are the sum of the two numbers above it. Here's an
example of the Pascal's Triangle of size 5.

    1
   1 1
  1 2 1
 1 3 3 1
1 4 6 4 1

Given an integer n, generate the n-th row of the Pascal's Triangle.
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

/* APPROACH 1: DP row by row. O(N^2) time, O(N) space */
vector<int> getNthPascalRow(int n) {
    if (n == 1) return {1};
    if (n == 2) return {1, 1};
    vector<int> prevRow = {1, 1};
    for (int row = 3; row <= n; row++) {
        vector<int> curRow = {1};
        for (int i = 0; i < prevRow.size() - 1; i++) {
            curRow.push_back(prevRow[i] + prevRow[i + 1]);
        }
        curRow.push_back(1);
        prevRow = curRow;
    }
    return prevRow;
}

/* APPROACH 2: Combinatorics. The N'th row of Pascal's Triangle is {(n-1) C 0}, {(n) C 1}, ...,
{(n-1) C (n-1)}. We can calculate combinations quickly using {n C k} = {n C (k-1)} * (n - k + 1) / k.
O(N) */
vector<int> getNthPascalRow2(int n) {
    if (n == 1) return {1};
    if (n == 2) return {1, 1};
    vector<int> row = {1};
    int prev = 1;
    for (int i = 1; i <= n - 1; i++) {
        int cur = (prev * (n - i)) / i;
        row.push_back(cur);
        prev = cur;
    }
    return row;
}

int main(int argc, char **argv) {
    int n = 6;

    cout << "APPROACH 1: ";
    print(getNthPascalRow(n));

    cout << "APPROACH 2: ";
    print(getNthPascalRow2(n));
    return 0;
}
