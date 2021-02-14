#include <iostream>
#include <vector>
using namespace std;

/*
Given a matrix that is organized such that the numbers will always be sorted left to right, and the first number of each
row will always be greater than the last element of the last row (mat[i][0] > mat[i - 1][-1]), search for a specific value
in the matrix and return whether it exists.

ex.
[
    [1, 3, 5, 8],
    [10, 11, 15, 16],
    [24, 27, 30, 31],
]
target = 10 -> true
target = 7 -> false
*/

/* APPROACH 1: Binary search first value among rows, then binary search in row.
To find row, search for index of floor in first column.
O(log(N) + log(M)) */
bool binarySearchInRow(vector<int> row, int target) {
    int n = row.size();
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = (l + r) / 2;
        if (target < row[m]) r = m - 1;
        else if (target > row[m]) l = m + 1;
        else return true;
    }
    return false;
}
int binarySearchForRow(vector<vector<int> > matrix, int target) {
    int m = matrix.size();
    int lRow = 0, rRow = m - 1, mRow = (lRow + rRow) / 2;
    while (lRow <= rRow) {
        mRow = (lRow + rRow) / 2;
        if (target > matrix[mRow][0]) {
            if (mRow == m - 1 || target < matrix[mRow + 1][0]) return mRow;
            lRow = mRow + 1;
        }
        else if (target < matrix[mRow][0]) rRow = mRow - 1;
        else return mRow;
    }
    return -1;
}
bool searchInMatrix(vector<vector<int> > matrix, int target) {
    int row = binarySearchForRow(matrix, target);
    return row >= 0 && binarySearchInRow(matrix[row], target);
}

int main(int argc, char **argv) {
    vector<vector<int> > matrix = {
        {1, 3, 5, 8},
        {10, 11, 15, 16},
        {24, 27, 30, 31},
    };
    int target = 10;
    cout << searchInMatrix(matrix, target) << '\n';
    return 0;
}
