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

/* APPROACH 2: Max heap. Heapify the array, remove largest k-1 elements, and return max. Also
runs in O(N log N) time. */
void heapify(int *arr, int n, int i) {
	if (i >= n) return;
	int lChild = 2*i+1;
	int rChild = 2*i+2;
	int maxIndex = i;
	if (lChild < n && arr[lChild] > arr[maxIndex]) maxIndex = lChild;
	if (rChild < n && arr[rChild] > arr[maxIndex]) maxIndex = rChild;
	if (maxIndex != i) {
		int temp = arr[i];
		arr[i] = arr[maxIndex];
		arr[maxIndex] = temp;
		heapify(arr, n, maxIndex);
	}
}
int kthLargest2(int *arr, int n, int k) {
	for (int i = n-1; i >= 0; i--) heapify(arr, n, i);
	for (int i = 1; i < k; i++) {
		int temp = arr[0];
		arr[0] = arr[n-1];
		arr[n-1] = temp;
		heapify(arr,n-1,0);
		n--;
	}
	/*for (int i = 0; i < n+k-1; i++) std::cout << arr[i] << " ";
	std::cout << '\n';*/
	return arr[0];
}

int main(int argc, char **argv) {
	int n = 6;
	int *arr = new int[6];
	arr[0]=3; arr[1]=5; arr[2]=2; arr[3]=4; arr[4]=6; arr[5]=8;
	std::cout << kthLargest(arr,n,3) << '\n';

	int *arr2 = new int[6];
	arr2[0]=3; arr2[1]=5; arr2[2]=2; arr2[3]=4; arr2[4]=6; arr2[5]=8;
	std::cout << kthLargest2(arr2,n,3) << '\n';
	return 0;
}
