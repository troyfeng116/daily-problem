#include <iostream>
using namespace std;

/*
N-Queens is the problem where you find a way to put n queens on a nxn chess board without them
being able to attack each other. Given an integer n, return 1 possible solution by returning
all the queens' positions.
*/

void printBoard(int **board, int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            std::cout << board[i][j] << " ";
        }
        std::cout << '\n';
    }
}

/* APPROACH 1: Backtracking. Place queens until a valid config is found, then return.
Worst case exponential time if no solutions for small boards. */
bool canPlaceQueen(int r, int c, int **board, int n) {
    for (int i = 0; i < n; i++) {
        if (board[r][i] == 1 || board[i][c] == 1) return false;
    }
    for (int i = r, j = c; i < n && j < n; i++, j++) {
        if (board[i][j] == 1) return false;
    }
    for (int i = r, j = c; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1) return false;
    }
    for (int i = r, j = c; i < n && j >= 0; i++, j--) {
        if (board[i][j] == 1) return false;
    }
    for (int i = r, j = c; i >= 0 && j < n; i--, j++) {
        if (board[i][j] == 1) return false;
    }
    return true;
}
bool backtrack(int row, int **board, int n) {
    if (row >= n) return true;
    for (int col = 0; col < n; col++) {
        if (canPlaceQueen(row, col, board, n)) {
            board[row][col] = 1;
            if (backtrack(row + 1, board, n)) return true;
            board[row][col] = 0;
        }
    }
    return false;
}
int **placeNQueens(int n) {
    int **ans = (int **) malloc(sizeof(int *) * n);
    for (int i = 0; i < n; i++) {
        ans[i] = (int *) malloc(sizeof(int) * n);
        for (int j = 0; j < n; j++) {
            ans[i][j] = 0;
        }
    }
    if (!backtrack(0, ans, n)) {
        std::cout << "There are no solutions to N Queens for n = " << n << '\n';
    }
    return ans;
}

int main(int argc, char **argv) {
    int n = 18;
    printBoard(placeNQueens(n), n);
    return 0;
}
