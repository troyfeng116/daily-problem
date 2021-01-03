#include <iostream>
#include <vector>
using namespace std;

/*
A Sudoku board is a 9x9 grid, where each row, column and each 3x3 subbox contains the number
from 1-9. Here's an example of some Sudoku boards.
-------------
|534|678|912|
|672|195|348|
|198|342|567|
|------------
|859|761|423|
|426|853|791|
|713|924|856|
|------------
|961|537|284|
|287|419|635|
|345|286|179|
|------------

Given a 9x9 board, determine if it is a valid Sudoku board. The board may be partially filled,
where an empty cell will be represented by a zero.
*/

/* APPROACH 1: Validate all rows, columns, and squares I guess. O(1) time since board is fixed
size */
bool checkVal(int val, vector<bool> &found) {
    if (val < 0 || val > 9) return false;
    if (val == 0) return true;
    if (found[val]) return false;
    found[val] = true;
    return true;
}
bool checkRowsAndCols(vector<vector<int> > board) {
    for (int i = 0; i < 9; i++) {
        vector<bool> foundInRow(10, false), foundInCol(10, false);
        for (int j = 0; j < 9; j++) {
            if (!checkVal(board[i][j], foundInRow) || !checkVal(board[j][i], foundInCol)) return false;
        }
    }
    return true;
}
bool checkSquares(vector<vector<int> > board) {
    const vector<vector<int> > dirs = {{0, 0}, {-1, 1}, {0, 1}, {1, 1}, {1, 0}, {1, -1}, {0, -1}, {-1, -1}, {-1, 0}};
    for (int row = 1; row < 9; row += 3) {
        for (int col = 1; col < 9; col += 3) {
            vector<bool> found(10, false);
            for (int d = 0; d < 9; d++) {
                if (!checkVal(board[row + dirs[d][0]][col + dirs[d][1]], found)) return false;
            }
        }
    }
    return true;
}
bool isValidSudoku(vector<vector<int> > board) {
    return checkRowsAndCols(board) && checkSquares(board);
}

int main(int argc, char **argv) {
    vector<vector<int> > board = {
        {5, 0, 4, 6, 7, 8, 9, 1, 0},
        {6, 0, 2, 1, 9, 5, 3, 4, 8},
        {1, 9, 8, 3, 4, 2, 5, 6, 7},
        {8, 5, 9, 7, 6, 1, 4, 2, 3},
        {4, 2, 6, 8, 5, 3, 7, 9, 1},
        {7, 1, 3, 9, 2, 4, 8, 5, 6},
        {9, 6, 1, 5, 3, 7, 2, 8, 4},
        {2, 8, 7, 4, 1, 9, 6, 3, 5},
        {3, 4, 5, 2, 8, 6, 1, 7, 9},
    };

    std::cout << isValidSudoku(board) << '\n';
    return 0;
}
