#include <iostream>
#include <vector>
using namespace std;

/*
A maze is a matrix where each cell can either be a 0 or 1. A 0 represents that the cell is empty, and a 1 represents a wall 
that cannot be walked through. You can also only travel either right or down.

Given a nxm matrix, find the number of ways someone can go from the top left corner to the bottom right corner. You can 
assume the two corners will always be 0.

Example:
Input: [[0, 1, 0], [0, 0, 1], [0, 0, 0]]
# 0 1 0
# 0 0 1
# 0 0 0
Output: 2
The only two paths that can be taken in the above example are:
down -> right -> down -> right
down -> down -> right -> right.
*/

/* APPROACH 1: DFS. No need to backtrack since once you're at a point and you make a move, you will never be able to go
back to that original point. Exponential time */
int dfs(vector<vector<int> > maze, int i, int j) {
    int m = maze.size(), n = maze[0].size();
    if (i == m-1 && j == n-1) return 1;
    int sum = 0;
    if (i + 1 < m && maze[i+1][j] != 1) sum += dfs(maze, i+1, j);
    if (j + 1 < n && maze[i][j+1] != 1) sum += dfs(maze, i, j+1);
    return sum;
}
int numPaths(vector<vector<int> > maze) {
    return dfs(maze, 0, 0);
}

/* APPROACH 2: DP. dp[i][j] = dp[i-1][j] + dp[i][j-1] but only if (i,j) is not a wall. O(M * N) */
int numPaths2(vector<vector<int> > maze) {
    int m = maze.size(), n = maze[0].size();
    vector<vector<int> > dp(m, vector<int>(n, 0));
    // Base cases.
    dp[0][0] = 1;
    for (int i = 1; i < m; i++) {
        if (maze[i][0] == 1) break;
        dp[i][0] = 1;
    }
    for (int j = 1; j < n; j++) {
        if (maze[0][j] == 1) break;
        dp[0][j] = 1;
    }
    for (int i = 1; i < m; i++) {
        for (int j = 1; j < n; j++) {
            if (maze[i][j] == 0) {
                dp[i][j] = dp[i-1][j] + dp[i][j-1];
            }
        }
    }
    return dp[m-1][n-1];
}

int main(int argc, char **argv) {
    vector<vector<int> > maze = {{0, 0, 0, 0}, {0, 0, 0, 0}, {0, 0, 0, 0}};
    std::cout << "APPROACH 1 TESTING: " << numPaths(maze) << '\n';
    std::cout << "APPROACH 2 TESTING: " << numPaths2(maze) << '\n';
    return 0;
}
