#include <iostream>
#include <vector>
#include <queue>
using namespace std;

/*
Find the maximum number of connected colors in a grid.

ex.
grid = [
    [1, 0, 0, 1],
    [1, 1, 1, 1],
    [0, 1, 0, 0]
]
-> 7
*/

/*
Question: more than 2 colors in {colors}? Will assume yes
*/

const int dirs[4][2] = {{1, 0}, {0, 1}, {-1, 0}, {0, -1}};

/* APPROACH 1: DFS. Treat each cell as a node in a graph with 4 edges, one to each
adjacent cell of the matrix. Keep array of visited cells. O(M * N) */
int dfs(vector<vector<int> > grid, int color, int i, int j, vector<vector<bool> > &visited) {
    int m = grid.size(), n = grid[0].size();
    visited[i][j] = true;
    int count = 0;
    if (grid[i][j] == color) {
        count++;
        for (int d = 0; d < 4; d++) {
            int i2 = i + dirs[d][0], j2 = j + dirs[d][1];
            if (i2 >= 0 && i2 < m && j2 >= 0 && j2 < n && !visited[i2][j2]) {
                count += dfs(grid, color, i2, j2, visited);
            }
        }
    }
    return count;
}
int maxConnectedColors(vector<vector<int> > grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<bool> > visited(m, vector<bool>(n, false));
    int ans = 0;
    for (int i = 0; i < m; i++) {
        for (int j = 0; j < n; j++) {
            if (!visited[i][j]) {
                ans = max(ans, dfs(grid, grid[i][j], i, j, visited));
            }
        }
    }
    return ans;
}

/* APPROACH 2: BFS. Queue to store nodes {i, j}. O(M * N) */
int maxConnectedColors2(vector<vector<int> > grid) {
    int m = grid.size(), n = grid[0].size();
    vector<vector<bool> > visited(m, vector<bool>(n, false));
    int ans = 0;
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            if (!visited[r][c]) {
                queue<pair<int, int> > q;
                int count = 0;
                q.push({r, c});
                while (!q.empty()) {
                    pair<int, int> node = q.front();
                    int i = node.first, j = node.second;
                    q.pop();
                    count++;
                    visited[i][j] = true;
                    for (int d = 0; d < 4; d++) {
                        int i2 = i + dirs[d][0], j2 = j + dirs[d][1];
                        if (i2 >= 0 && i2 < m && j2 >= 0 && j2 < n && grid[i2][j2] == grid[i][j] && !visited[i2][j2]) {
                            q.push({i2, j2});
                        }
                    }
                }
                ans = max(count, ans);
            }
        }
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<vector<int> > grid = {
        {1, 0, 0, 1},
        {1, 1, 1, 1},
        {0, 1, 0, 0},
    };
    
    std::cout << "APPROACH 1 TESTING: " << maxConnectedColors(grid) << '\n';
    std::cout << "APPROACH 2 TESTING: " << maxConnectedColors2(grid) << '\n';
    return 0;
}
