#include <iostream>
#include <string>
using namespace std;

/*
You are given a 2D array of characters, and a target string. Return whether or not the word 
target word exists in the matrix. Unlike a standard word search, the word must be either going 
left-to-right, or top-to-bottom in the matrix.

Example:

[['F', 'A', 'C', 'I'],
 ['O', 'B', 'Q', 'P'],
 ['A', 'N', 'O', 'B'],
 ['M', 'A', 'S', 'S']]

Given this matrix, and the target word FOAM, you should return true, as it can be found going 
up-to-down in the first column.
*/

/*
For each possible starting position, if first letters match, DFS in each direction.
*/
bool searchVert(string word, char **board, int row, int col) {
	for (int i = 0; i < word.length(); i++) {
		if (word.at(i) != board[row+i][col]) return false;
	}
	return true;
}
bool searchHoriz(string word, char **board, int row, int col) {
	for (int i = 0; i < word.length(); i++) {
		if (word.at(i) != board[row][col+i]) return false;
	}
	return true;
}
bool wordExists(string word, char **board, int m, int n) {
	int len = word.length();
	for (int row = 0; row < m; row++) {
		for (int col = 0; col < n; col++) {
			if (board[row][col] == word.at(0)) {
				if (row <= m-len) {
					if (searchVert(word, board, row, col)) return true;
				}
				if (col <= n-len) {
					if (searchHoriz(word, board, row, col)) return true;
				}
			}
		}
	}
	return false;
}

int main(int argc, char **argv) {
	char **board;
	board = new char *[4];
	for (int i = 0; i < 4; i++) board[i] = new char[4];
	board[0][0] = 'F'; board[0][1] = 'A'; board[0][2] = 'C'; board[0][3] = 'I';
	board[1][0] = 'O'; board[1][1] = 'B'; board[1][2] = 'Q'; board[1][3] = 'P';
	board[2][0] = 'A'; board[2][1] = 'N'; board[2][2] = 'O'; board[2][3] = 'B';
	board[3][0] = 'M'; board[3][1] = 'A'; board[3][2] = 'S'; board[3][3] = 'S';
	string target = "IP";
	std::cout << wordExists(target, board, 4, 4) << '\n';
	return 0;
}
