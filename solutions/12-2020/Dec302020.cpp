#include <iostream>
#include <vector>
using namespace std;

/*
Given a square 2D matrix (n x n), rotate the matrix by 90 degrees clockwise.

ex.
1 2 3
4 5 6
7 8 9
 =>
7 4 1
8 5 2
9 6 3
*/

void print(vector<vector<int> > mat) {
    for (int i = 0; i < mat.size(); i++) {
        for (int j = 0; j < mat[0].size(); j++) {
            std::cout << mat[i][j] << " ";
        }
        std::cout << '\n';
    }
}

/* APPROACH 1: Traverse original matrix row by row, bottom up and left to right.
Then fill new array column by column, left to right and top to bottom.
O(N^2) time and space */
vector<vector<int> > rotateMatrix(vector<vector<int> > mat) {
    int n = mat.size();
    vector<vector<int> > ans(n, vector<int>(n, 0));
    for (int row = n-1; row >= 0; row--) {
        for (int col = 0; col < n; col++) {
            ans[col][n - row - 1] = mat[row][col];
        }
    }
    std::cout << "DONE\n";
    return ans;
}

/* APPROACH 2: Rotate each square "shell" from outmost square layer to innermost.
Starting from top-left of square, rotate each element on each of the 4 sides.
O(M*N) time, O(1) space */
void rotateMatrix2(vector<vector<int> > &mat) {
    int n = mat.size();
    // Consider all square layers one by one
    for (int x = 0; x < n / 2; x++) {
        // For each element on each side of current square layer
        for (int y = x; y < n - x - 1; y++) {
            // Store value on top side in temp variable
            int temp = mat[x][y]; 
            // Move value from left to top 
            mat[x][y] = mat[n - 1 - y][x];
            // Move value from bottom to left
            mat[n - 1 - y][x] = mat[n - 1 - x][n - 1 - y];
            // Move value from right to bottom
            mat[n - 1 - x][n - 1 - y] = mat[y][n - 1 - x];
            // Fill right with temp to complete rotate cycle
            mat[y][n - 1 - x] = temp;
        }
    }
}

int main(int argc, char **argv) {
    vector<vector<int> > matrix = {
        {1, 2, 3},
        {4, 5, 6},
        {7, 8, 9},
    };

    std::cout << "APPROACH 1 TESTING:\n";
    print(rotateMatrix(matrix));

    std::cout << "APPROACH 2 TESTING:\n";
    rotateMatrix2(matrix);
    print(matrix);
    return 0;
}
