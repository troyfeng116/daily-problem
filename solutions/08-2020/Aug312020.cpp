#include <iostream>
using namespace std;

/*
You are given a 2D array of integers. Print out the clockwise spiral traversal of the matrix.

Example:

grid = [[1,  2,  3,  4,  5],
        [6,  7,  8,  9,  10],
        [11, 12, 13, 14, 15],
        [16, 17, 18, 19, 20]]

The clockwise spiral traversal of this array is:

1, 2, 3, 4, 5, 10, 15, 20, 19, 18, 17, 16, 11, 6, 7, 8, 9, 14, 13, 12
*/

void printSpiralAux(int ** arr, int start, int m, int n) {
	for (int j = start; j < n-start; j++) {
		std::cout << arr[start][j] << " ";
	}
	for (int i = start+1; i < m-start; i++) {
		std::cout << arr[i][n-start-1] << " ";
	}
	for (int j = n-start-2; j >= start; j--) {
		std::cout << arr[m-start-1][j] << " ";
	}
	for (int i = m-start-2; i > start; i--) {
		std::cout << arr[i][start] << " ";
	}
}
void printSpiral(int **arr, int m, int n) {
	for (int start = 0; start < min(m/2, n/2); start++) {
		printSpiralAux(arr, start, m, n);
	}
	std::cout << "\n";
}

int main(int argc, char **argv) {
	int m = 10, n = 5;
	int **test = new int*[m];
	for (int i = 0; i < m; i++) {
		test[i] = new int[n];
		for (int j = i*n; j < (i+1)*n; j++) {
			test[i][j-i*n] = j+1;
		}
	}
	printSpiral(test, m, n);
	return 0;
}
