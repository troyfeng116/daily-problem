#include <iostream>
#include <vector>
using namespace std;

/*
Reshaping a matrix means to take the same elements in a matrix but change the row and column length.
This means that the new matrix needs to have the same elements filled in the same row order as the old
matrix. Given a matrix, a new row size x and a new column size y, reshape the matrix. If it is not
possible to reshape, return None.
*/

void printMat(vector<vector<int> > mat) {
    if (mat.size() == 0 || mat[0].size() == 0) {
        cout << "NONE\n";
        return;
    }
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++) {
            cout << mat[i][j] << " ";
        }
        cout << '\n';
    }
}

/* APPROACH 1: Create new matrix and populate it row by row. O(X*Y) */
vector<vector<int> > reshapeMatrix(vector<vector<int> > mat, int x, int y) {
    int m = mat.size(), n = mat[0].size();
    if (m * n != x * y) return {{}};
    vector<vector<int> > ans(y, vector<int>(x, 0));
    for (int i = 0; i < m * n; i++) {
        ans[i / x][i % x] = mat[i / n][i % n];
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<vector<int> > mat = {{1, 2}, {3, 4}};
    int x = 1, y = 4;
    printMat(reshapeMatrix(mat, x, y));
    return 0;
}
