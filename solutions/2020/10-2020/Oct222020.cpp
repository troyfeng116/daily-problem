#include <iostream>
#include <vector>
using namespace std;

/*
Given a sorted list of positive numbers, find the smallest positive number that cannot be a sum of any 
subset in the list.

Example:
Input: [1, 2, 3, 8, 9, 10]
Output: 7
Numbers 1 to 6 can all be summed by a subset of the list of numbers, but 7 cannot.
*/

/*
QUESTIONS:
-bound on largest number in list (i.e. can index array to largest)?
-duplicates?
Since powers of 2 from 0 to n-1 define basis for {[1, 2^n)}, an array of length 30
could cover all positive integers up to INT_MAX. Overflow? Will assume no
*/

/* APPROACH 1: Suppose arr[0,i-1] can form all integers from 1 to x-1. Then if arr[i] <= x, we will
be able to form all integers from 1 to x+arr[i]-1. i.e. say the first 10 elements can generate sums
from 1,2,3,...,55. If the 11th element were 56, we would be able to generate 1,2,3,...,111. If the 11th
element were 57 or greater, we would have no way of generating 56.
O(N) time */
int smallestNoSubsetSum(vector<int> arr) {
    // x is the smallest integer that can't be generated from subset sum
    int x = 1;
    // As long as arr[i] <= x, then we can take a subset of arr[0,i] to form any integer < x+arr[i].
    for (int i = 0; i < arr.size() && arr[i] <= x; i++) x += arr[i];
    return x;
}

int main(int argc, char **argv) {
    vector<int> arr = {1, 2, 3, 8, 9, 10};
    std::cout << smallestNoSubsetSum(arr) << '\n';
    return 0;
}
