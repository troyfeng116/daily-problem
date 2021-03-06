#include <iostream>
using namespace std;

/*
You are given an array of integers. Find the maximum sum of all possible contiguous subarrays of the array.

Example:

[34, -50, 42, 14, -5, 86]

Given this input array, the output should be 137. The contiguous subarray with the largest sum is [42, 14, -5, 86].

Your solution should run in linear time.
*/

/* APPROACH 1: Sliding window/nested loop. Runs in O(N^2) */
int maxContigSum1(int *arr, int n) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        int sum = 0;
        for (int j = i; j < n; j++) {
            sum += arr[j];
            max = std::max(sum, max);
        }
    }
    return max;
}

/* APPROACH 2: Divide and conquer. Given (l,r) and m=(l+r)/2, find max contig sum in L and R halves recursively, and then
compare to max contig sum across middle. Splitting is log(N), each max contig sum including middle can be found in O(N) for
total O(N log N) */
int maxMiddleSum(int *arr, int l, int r) {
    int m = (l+r)/2;
    int maxLeft = 0;
    int sumLeft = 0;
    for (int i = m-1; i >= l; i--) {
        sumLeft += arr[i];
        if (sumLeft > maxLeft) maxLeft = sumLeft;
    }
    int maxRight = 0;
    int sumRight = 0;
    for (int i = m+1; i <= r; i++) {
        sumRight += arr[i];
        if (sumRight > maxRight) maxRight = sumRight;
    }
    return arr[m] + maxLeft + maxRight;
}
int divideAndConquer(int *arr, int l, int r) {
    if (l >= r) return arr[l];
    int m = (l+r)/2;
    return max( max(divideAndConquer(arr, l, m-1), divideAndConquer(arr, m+1, r)), 
                maxMiddleSum(arr, l, r));
}
int maxContigSum2(int *arr, int n) {
    return divideAndConquer(arr, 0, n-1);
}

/* APPROACH 3: One pass tracking max so far, max including current index. At each index, max conig subarray either includes
arr[i] or doesn't include arr[i]. If adding arr[i] makes the sum smaller than arr[i], we should just start from arr[i]. Else
we include arr[i] and move on. Basically checks all positive subarray sums. O(N) */
int maxContigSum3(int *arr, int n) {
    int maxSoFar = 0;
    int maxIncludingThis = 0;
    for (int i = 0; i < n; i++) {
        maxIncludingThis = std::max(maxIncludingThis+arr[i], arr[i]);
        maxSoFar = std::max(maxSoFar, maxIncludingThis);
    }
    return maxSoFar;
}

int main(int argc, char **argv) {
    int n = 6;
    int arr[] = { 34, -50, 42, 14, -5, 86 };
    std::cout << maxContigSum1(arr, n) << '\n';
    std::cout << maxContigSum2(arr, n) << '\n';
    std::cout << maxContigSum3(arr, n) << '\n';
    return 0;
}
