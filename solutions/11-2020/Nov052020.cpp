#include <iostream>
#include <vector>
using namespace std;

/*
Design a Tic-Tac-Toe game played between two players on an n x n grid. A move is guaranteed to be valid, and 
a valid move is one placed on an empty block in the grid. A player who succeeds in placing n of their marks 
in a horizontal, diagonal, or vertical row wins the game. Once a winning condition is reached, the game ends 
and no more moves are allowed. Below is an example game which ends in a winning condition:

Given n = 3, assume that player 1 is "X" and player 2 is "O" 
board = TicTacToe(3);

board.move(0, 0, 1); -> Returns 0 (no one wins)
|X| | |
| | | |    // Player 1 makes a move at (0, 0).
| | | |

board.move(0, 2, 2); -> Returns 0 (no one wins)
|X| |O|
| | | |    // Player 2 makes a move at (0, 2).
| | | |

board.move(2, 2, 1); -> Returns 0 (no one wins)
|X| |O|
| | | |    // Player 1 makes a move at (2, 2).
| | |X|

board.move(1, 1, 2); -> Returns 0 (no one wins)
|X| |O|
| |O| |    // Player 2 makes a move at (1, 1).
| | |X|

board.move(2, 0, 1); -> Returns 0 (no one wins)
|X| |O|
| |O| |    // Player 1 makes a move at (2, 0).
|X| |X|

board.move(
 1, 0, 2); -> Returns 0 (no one wins)
|X| |O|
|O|O| |    // Player 2 makes a move at (1, 0).
|X| |X|

board.move(2, 1, 1); -> Returns 1 (player 1 wins)
|X| |O|
|O|O| |    // Player 1 makes a move at (2, 1).
|X|X|X|
*/

/* QUESTION: Need to block illegal moves (i.e. already occupied)? Will assume no */

/* APPROACH 1: When move made, check row, col, and diag/antidiag if applicable. O(N) per move, O(N^2) space */
class TicTacToe {
public:
    TicTacToe(int n) {
        board.resize(n, vector<int>(n, 0));
    }
    int makeMove(int row, int col, int player) {
        board[row][col] = player;
        int n = board.size();
        int r = 0, c = 0;
        // Check same col
        for (r = 1; r < n; r++) {
            if (board[r][col] != board[r-1][col]) break;
        }
        if (r == n) return player;
        // Check same row
        for (c = 1; c < n; c++) {
            if (board[row][c] != board[row][c-1]) break;
        }
        if (c == n) return player;
        // Check diagonal
        if (row == col) {
            for (r = 1; r < n; r++) {
                if (board[r][r] != board[r - 1][r - 1]) break;
            }
            if (r == n) return player;
        }
        // Check antidiagonal
        if (row + col == n - 1) {
            for (r = 1; r < n; r++) {
                if (board[n - r - 1][r] != board[n - r][r - 1]) break;
            }
            if (r == n) return player;
        }
        return 0;
    }
    void print() {
        int n = board.size();
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                std::cout << "|" << board[i][j];
            }
            std::cout << "|\n";
        }
    }
private:
    vector<vector<int> > board;
};

/* APPROACH 2: We can check if a move leads to a winner in O(1). We can store the net number of X/Os in each
row, col, and diag/antidiag. There are n rows and n cols, plus 1 diag/antidiag we need to track. So we use
O(N) space for rows+cols and one extra variable for diag/antidiag. If player one moves, net X/O of the
row/col/diag of that move goes up by 1. If player 2 moves, net X/O goes down by 1. If any net X/O is equal to 
N after a move, that player wins. O(1) per move, O(N) space */
class TicTacToe2 {
public:
    TicTacToe2(int n) {
        rowsNetXO.resize(n, 0);
        colsNetXO.resize(n, 0);
        diagNetXO = 0;
        antidiagNetXO = 0;
    }
    int makeMove(int row, int col, int player) {
        int n = rowsNetXO.size();
        int netChange = player == 1 ? 1 : -1;
        rowsNetXO[row] += netChange;
        if (rowsNetXO[row] == n) return player;
        colsNetXO[col] += netChange;
        if (colsNetXO[col] == n) return player;
        if (row == col) {
            diagNetXO += netChange;
            if (diagNetXO == n) return player;
        }
        if (row + col == n-1) {
            antidiagNetXO += netChange;
            if (antidiagNetXO == n) return player;
        }
        return 0;
    }
private:
    vector<int> rowsNetXO;
    vector<int> colsNetXO;
    int diagNetXO;
    int antidiagNetXO;
};

int main(int argc, char **argv) {
    vector<vector<int> > moves = {
        {0,0,1},
        {0,2,2},
        {2,2,1},
        {1,1,2},
        {2,0,1},
        {1,0,2},
        {2,1,1},
    };
    // APPROACH 1 TESTING
    TicTacToe *board1 = new TicTacToe(3);
    std::cout << "---- APPROACH 1 TESTING ----\n";
    for (int i = 0; i < moves.size(); i++) {
        std::cout << "WINNER: " << (*board1).makeMove(moves[i][0], moves[i][1], moves[i][2]) << '\n';
        (*board1).print();
        std::cout << "----------\n";
    }

    // APPROACH 2 TESTING
    TicTacToe2 *board2 = new TicTacToe2(3);
    std::cout << "---- APPROACH 2 TESTING ----\n";
    for (int i = 0; i < moves.size(); i++) {
        std::cout << "WINNER: " << (*board2).makeMove(moves[i][0], moves[i][1], moves[i][2]) << '\n';
        std::cout << "----------\n";
    }

    return 0;
}
