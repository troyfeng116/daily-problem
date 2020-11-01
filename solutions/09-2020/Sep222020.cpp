#include <iostream>
#include <vector>
using namespace std;

/*
Daily Interview Pro
Hi, here's your problem today. This problem was recently asked by LinkedIn:

Given a 2-dimensional grid consisting of 1's (land blocks) and 0's (water blocks), count the 
number of islands present in the grid. The definition of an island is as follows:
1) Must be surrounded by water blocks.
2) Consists of land blocks (1's) connected to adjacent land blocks (either vertically or 
horizontally).
Assume all edges outside of the grid are water.

Example:
Input: 
10001
11000
10110
00000

Output: 3
*/

const int directions[][2] = {{0,1},{1,0},{0,-1},{-1,0}};

/* APPROACH 1: Search for 1s and BFS a la fill algorithm, marking visited points. O(M*N) time and
space */
bool isLegal(vector<vector<int >> grid, int m, int n, int i, int j, bool **visited) {
    return i >= 0 && i < m && j >= 0 && j < n && !visited[i][j];
}
void fill(vector<vector<int >> grid, int m, int n, int i, int j, bool **visited) {
    visited[i][j] = true;
    for (int d = 0; d < 4; d++) {
        int i2 = i+directions[d][0];
        int j2 = j+directions[d][1];
        if (isLegal(grid, m, n, i2, j2, visited) && grid[i2][j2] == 1) {
            fill(grid, m, n, i2, j2, visited);
        }
    }
}
int numIslands(vector<vector<int >> grid, int m, int n) {
    bool **visited = new bool*[m];
    for (int i = 0; i < m; i++) {
        visited[i] = new bool[n];
        for (int j = 0; j < n; j++) {
            visited[i][j] = false;
        }
    }

    int islands = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (grid[i][j] == 1 && !visited[i][j]) {
                fill(grid, m, n, i, j, visited);
                islands++;
            }
        }
    }
    return islands;
}

int main(int argc, char **argv) {
    int m = 4, n = 5;
    vector<vector<int> > test;
    test.push_back({1,0,0,0,1});
    test.push_back({1,1,0,0,0});
    test.push_back({1,0,1,1,0});
    test.push_back({0,0,0,0,0});
    std::cout << numIslands(test, m, n) << '\n';
    return 0;
}
