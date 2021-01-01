#include <iostream>
using namespace std;

/*
Given an array with n objects colored red, white or blue, sort them in-place so that objects of 
the same color are adjacent, with the colors in the order red, white and blue.

Here, we will use the integers 0, 1, and 2 to represent the color red, white, and blue 
respectively.

Note: You are not suppose to use the library’s sort function for this problem.

Can you do this in a single pass?

Example:
Input: [2,0,2,1,1,0]
Output: [0,0,1,1,2,2]
*/

/* APPROACH 1: Just maintain counts of 0, 1, and 2 and place them manually. O(N) time but not
in place or single pass */
void sortThreeColors1(int *arr, int n) {
    int red = 0, white = 0, blue = 0;
    for (int i = 0; i < n; i++) {
        if (arr[i] == 0) red++;
        else if (arr[i] == 1) white++;
        else blue++;
    }
    for (int i = 0; i < red; i++) {
        arr[i] = 0;
    }
    for (int i = red; i < red+white; i++) {
        arr[i] = 1;
    }
    for (int i = red+white; i < red+white+blue; i++) {
        arr[i] = 2;
    }
}

/* APPROACH 2: Partition a la quickSort. [0,l) is all zeroes, [l,m) is ones, [m,r) unsorted,
[r,n) twos. O(N) time, one pass */
void sortThreeColors2(int *arr, int n) {
    int l = 0;
    int m = 0;
    int r = n-1;
    while (m <= r) {
        if (arr[m] == 0) {
            arr[m] = arr[l];
            arr[l] = 0;
            l++;
            m++;
        }
        else if (arr[m] == 2) {
            arr[m] = arr[r];
            arr[r] = 2;
            r--;
        }
        else m++;
    }
}

int main(int argc, char **argv) {
    int n = 10;
    int test1[] = {2,0,2,1,1,0,1,0,1,1};
    sortThreeColors1(test1, n);
    for (int i = 0; i < n; i++) std::cout << test1[i] << ' ';
    std::cout << '\n';

    int test2[] = {2,0,2,1,1,0,0,2,2,2};
    sortThreeColors2(test2, n);
    for (int i = 0; i < n; i++) std::cout << test2[i] << ' ';
    std::cout << '\n';
    return 0;
}
