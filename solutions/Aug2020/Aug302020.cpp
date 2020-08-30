#include <iostream>
using namespace std;

/*
Given a list, find the k-th largest element in the list.
Input: list = [3, 5, 2, 4, 6, 8], k = 3
Output: 5
*/

/* APPROACH 1: Sort and return element at index n-k. Runs in O(N log N) */
void sort(int *arr, int l, int r) {
	if (l >= r) return;
	int splitter = arr[r];
	int m = l;
	for (int i = l; i < r; i++) {
		if (arr[i] < splitter) {
			int temp = arr[i];
			arr[i] = arr[m];
			arr[m] = temp;
			m++;
		}
	}
	arr[r] = arr[m];
	arr[m] = splitter;
	sort(arr,l,m-1);
	sort(arr,m+1,r);
}
int kthLargest(int* arr, int n, int k) {
	sort(arr, 0, n-1);
	return arr[n-k];
}

int main(int argc, char **argv) {
	int n = 6;
	int *arr = new int[6];
	arr[0]=3; arr[1]=5; arr[2]=2; arr[3]=4; arr[4]=6; arr[5]=8;
	std::cout << kthLargest(arr,n,3) << '\n';
	return 0;
}
