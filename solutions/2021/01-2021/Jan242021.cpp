#include <iostream>
#include <vector>
using namespace std;

/*
Given a matrix, transpose it. Transposing a matrix means the rows are now the column and vice-versa.
ex. {{1, 2, 3}, {4, 5, 6}} => {{1, 4}, {2, 5}, {3, 6}}
*/

void print(vector<vector<int> > mat) {
    int m = mat.size(), n = mat[0].size();
    for (int r = 0; r < m; r++) {
        for (int c = 0; c < n; c++) {
            std::cout << mat[r][c] << " ";
        }
        std::cout << "\n";
    }
}

/* APPROACH 1: Loop through and transpose. O(M * N) */
vector<vector<int> > transpose(vector<vector<int> > mat) {
    int m = mat.size(), n = mat[0].size();
    vector<vector<int> > ans(n, vector<int>(m, 0));
    for (int c = 0; c < n; c++) {
        for (int r = 0; r < m; r++) {
            ans[c][r] = mat[r][c];
        }
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<vector<int> > matrix = {{1, 2, 3}, {4, 5, 6}};
    print(transpose(matrix));
    return 0;
}
