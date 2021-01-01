#include <iostream>
#include <vector>
using namespace std;

/*
A chess board is an 8x8 grid. Given a knight at any position (x, y) and a number of moves k, we 
want to figure out after k random moves by a knight, the probability that the knight will still 
be on the chessboard. Once the knight leaves the board it cannot move again and will be considered 
off the board.

ex. x = 0, y = 0, k = 1 -> 0.25
*/

/* QUESTION: are board indices (x,y) 0 or 1 based? will assume 0 based */

/* APPROACH 1: DFS. Count all sequences of k moves that stay on board. O(8^k) */
const vector<vector<int>> moves = {{2,1}, {2,-1}, {1,-2}, {-1,-2}, {-2,-1}, {-2, 1}, {-1, 2}, {1, 2}};
bool isOnBoard(int i, int j) {
    return i >= 0 && i < 8 && j >= 0 && j < 8;
}
// Return number of sequences staying on board after movesLeft moves.
int dfs(int i, int j, int movesLeft) {
    if (isOnBoard(i, j)) {
        if (movesLeft == 0) {
            return 1;
        }
        int successes = 0;
        for (int d = 0; d < 8; d++) {
            successes += dfs(i + moves[d][0], j + moves[d][1], movesLeft - 1);
        }
        return successes;
    }
    else return 0;
}
double probabilityStayOnBoard(int startRow, int startCol, int k) {
    double total = pow(8, k);
    int successes = dfs(startRow, startCol, k);
    return (double) successes/total;
}

/* APPROACH 2: DP. Let dp[i][j][moves] = Probability knight is still on board after `moves` moves.
Then dp[i][j][moves] = SUM of all probabilities that knight is on board in adjacent legal squares.
O(K) time assuming constant N=8 (else O(K * N^2))
O(1) space assuming constant N=8 (else O(N^2)) */
double probabilityStayOnBoard2(int startRow, int startCol, int k) {
    vector<vector<double>> dp(8, vector<double>(8, 0.0));
    dp[startRow][startCol] = 1;
    for (int move = 0; move < k; move++) {
        vector<vector<double>> next_dp(8, vector<double>(8, 0.0));
        for (int i = 0; i < 8; i++) {
            for (int j = 0; j < 8; j++) {
                for (int d = 0; d < 8; d++) {
                    int i2 = i+moves[d][0];
                    int j2 = j+moves[d][1];
                    if (isOnBoard(i2, j2)) {
                        next_dp[i][j] += dp[i2][j2] / 8.0;
                    }
                }
            }
        }
        dp = next_dp;
    }
    double ans = 0.0;
    for (int i = 0; i < 8; i++) {
        for (int j = 0; j < 8; j++) {
            ans += dp[i][j];
        }
    }
    return ans;
}

int main(int argc, char **argv) {
    std::cout << "APPROACH 1 TESTING: " << probabilityStayOnBoard(2, 3, 10) << '\n';
    std::cout << "APPROACH 2 TESTING: " << probabilityStayOnBoard2(2, 3, 10) << '\n';
    return 0;
}