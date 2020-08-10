#include <iostream>
#include <vector>
using namespace std;

/* 
Given a sorted array, A, with possibly duplicated elements, find the indices of the first and last
occurrences of a target element, x. Return -1 if the target is not found.

Example:
Input: A = [1,3,3,5,7,8,9,9,9,15], target = 9
Output: [6,8]

Input: A = [100, 150, 150, 153], target = 150
Output: [1,2]

Input: A = [1,2,3,4,5,6,10], target = 9
Output: [-1, -1]
*/

/* Binary search for first occurrence of x in arr. */
int searchFirst(int arr[], int N, int x, int l, int r) {
	if (l > r) return -1;
	int m = (l+r)/2;
	/* If arr[m] is target and it is first occurrence of target, return m. */
	if ((m == 0 || (arr[m-1] < arr[m])) && arr[m] == x) return m;
	if (x > arr[m]) return searchFirst(arr, N, x, m+1, r);
	/* If arr[m] is target and is NOT first occurrence, binary search to left. */
	return searchFirst(arr, N, x, l, m-1);
}

/* Binary search for last occurrence of x in arr. */
int searchLast(int arr[], int N, int x, int l, int r) {
	if (l > r) return -1;
	int m = (l+r)/2;
	/* If arr[m] is target and it is last occurrence of target, return m. */
	if ((m == N-1 || arr[m] < arr[m+1]) && arr[m] == x) return m;
	if (x < arr[m]) return searchLast(arr,N,x,l,m-1);
	/* If arr[m] is target and it is NOT last occurrence of target, binary search to right. */
	return searchLast(arr,N,x,m+1,r);
}

int* findFirstLast(int arr[], int x) {
	int N = *(&arr+1)-arr;
	int *ans = new int[2];
	ans[0] = searchFirst(arr,N,x,0,N-1);
	ans[1] = searchLast(arr,N,x,0,N-1);
	return ans;
}

int main(int argc, char **argv) {
	int test[] = {100, 150, 150, 153};
	int *res = findFirstLast(test,150);
	std::cout << res[0] << ' ' << res[1] << '\n';
	return 0;
}
