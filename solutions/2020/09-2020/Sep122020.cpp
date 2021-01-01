#include <iostream>
using namespace std;

/*
You are given an array of integers. Return the smallest positive integer that is not present in the 
array. The array may contain duplicate entries.

For example, the input [3, 4, -1, 1] should return 2 because it is the smallest positive integer 
that doesn't exist in the array.

Your solution should run in linear time and use constant space.
*/

/* APPROACH 1: In an array of N integers, the largest integer that can be not present is N+1. So
we can loop through the array. If arr[i] <= N, swap it to its correct spot at arr[arr[i]-1]. */
int firstMissingInteger(int *arr, int n) {
    int i = 0;
    while (i < n) {
        if (arr[i] <= n && arr[i] >= 1 && arr[i] != i+1) {
            int temp = arr[i];
            arr[i] = arr[temp-1];
            arr[temp-1] = temp;
        }
        else i++;
    }
    for (int i = 0; i < n; i++) {
        if (arr[i] != i+1) return i+1;
    }
    return n+1;
}

int main(int argc, char **argv) {
    int n = 10;
    int arr[] = {1,2,3,4,5,8,6,7,9,10};
    std::cout << firstMissingInteger(arr, n) << '\n';
    return 0;
}
