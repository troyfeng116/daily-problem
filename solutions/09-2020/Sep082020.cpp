#include <iostream>
using namespace std;

/*
You have a landscape, in which puddles can form. You are given an array of non-negative 
integers representing the elevation at each location. Return the amount of water that 
would accumulate if it rains.

For example: [0,1,0,2,1,0,1,3,2,1,2,1] should return 6 because 6 units of water can get 
trapped here.
*/

/* APPROACH 1: Track height of highest wall to the right and left. Amout of water in
spot i is just the lower of the two walls to each side, minus height of current wall.
O(N) time and space. */
int waterTrapped(int *heights, int n) {
    int *left = new int[n];
    int *right = new int[n];
    for (int i = 0; i < n; i++) {
        left[i] = 0;
        right[i] = 0;
    }
    for (int i = 1; i < n; i++) {
        left[i] = std::max(heights[i], left[i-1]);
        right[n-i-1] = std::max(heights[n-i-1], right[n-i]);
    }
    int ans = 0;
    for (int i = 1; i < n-1; i++) {
        ans += std::min(left[i], right[i]) - heights[i];
    }
    return ans;
}

int main(int argc, char **argv) {
    int n = 12;
    int test[] = {0,1,0,2,1,0,1,3,2,1,2,1};
    std::cout << waterTrapped(test, n) << '\n';
    return 0;
}
