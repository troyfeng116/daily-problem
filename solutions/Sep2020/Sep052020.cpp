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

/* APPROACH 2: Divide and conquer. */
int maxContigSum2(int *arr, int n) {
    return 0;
}

/* APPROACH 3: One pass tracking max so far, max including current index. At each index, max conig subarray either includes
arr[i] or doesn't include arr[i]. If adding arr[i] makes the sum smaller than arr[i], we should just start from arr[i]. Else
we include arr[i] and move on. O(N) */
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
    std::cout << maxContigSum3(arr, n) << '\n';
    return 0;
}
