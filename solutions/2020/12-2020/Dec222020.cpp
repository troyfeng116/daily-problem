#include <iostream>
#include <vector>
using namespace std;

/*
Given a 2d n x m matrix where each cell has a certain amount of change on the floor, your goal is to
start from the top left corner mat[0][0] and end in the bottom right corner mat[n - 1][m - 1] with the
most amount of change. You can only move either right or down.
*/

/* APPROACH 1: DP. Let dp[i][j] = max change collectable after reaching (i,j). Then
dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + matrix[i][j].
Classic DP, O(M*N) */
int maxChange(vector<vector<int> > matrix) {
    int N = matrix.size(), M = matrix[0].size();
    vector<vector<int> > dp(N, vector<int>(M, 0));
    dp[0][0] = matrix[0][0];
    /* Base cases: max change along leftmost column and topmost row can only be made by moving
    only down or only right, respectively. */
    for (int r = 1; r < N; r++) {
        dp[r][0] = dp[r-1][0] + matrix[r][0];
    }
    for (int c = 1; c < M; c++) {
        dp[0][c] = dp[0][c-1] + matrix[0][c];
    }
    /* Fill DP bottom-up */
    for (int i = 1; i < N; i++) {
        for (int j = 1; j < M; j++) {
            dp[i][j] = max(dp[i-1][j], dp[i][j-1]) + matrix[i][j];
        }
    }
    return dp[N-1][M-1];
}

int main(int argc, char **argv) {
    vector<vector<int> > matrix = {
        {0, 3, 0, 2},
        {1, 2, 3, 3},
        {6, 0, 3, 2}
    };

    std::cout << maxChange(matrix) << '\n';
    return 0;
}
