#include <iostream>
#include <vector>
using namespace std;

/*
Starting at index 0, for an element n at index i, you are allowed to jump at most n indexes ahead. Given a 
list of numbers, find the minimum number of jumps to reach the end of the list.

Example:
Input: [3, 2, 5, 1, 1, 9, 3, 4]
Output: 2
Explanation:

The minimum number of jumps to get to the end of the list is 2:
3 -> 5 -> 4
*/

/* QUESTION: only positive numbers/jumps? */

void print(vector<int> arr) {
    std::cout << "[";
    for(int i = 0; i < arr.size()-1; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[arr.size()-1] << "]\n";
}

/* APPROACH 1: Kind of brute force. At each landing point, calculate next landing point greedily. O(N^2) */
int nextJump(vector<int> arr, int l, int r) {
    if (r >= arr.size()-1) return arr.size()-1;
    int maxIndex = l;
    for (int i = l+1; i <= r && i < arr.size(); i++) {
        if (arr[i] > arr[maxIndex]) {
            maxIndex = i;
        }
    }
    return maxIndex;
}
int minJumps(vector<int> nums) {
    int n = nums.size();
    vector<int> range(n);
    
    for (int i = 0; i < n; i++) {
        range[i] = nums[i] + i;
    }
    int jumps = 0;
    int i = 0;
    while (i < n-1) {
        std::cout << "JUMPED TO " << nextJump(nums, i+1, nums[i]+i) << '\n';
        i = nextJump(range, i+1, nums[i]+i);
        jumps++;
    }
    return jumps;
}

/* APPROACH 2: Similar to approach 1, but store maxNextDistance so we don't have to recalculate it when
we jump. O(N) */
int minJumps2(vector<int> nums) {
    if (nums.size() < 2) {
        return 0;
    }
    int jumps = 1;
    int i = 1;
    // max distance left for us to move currently
    int curMaxDistance= nums[0];
    // max distance we can move after the next jump
    int nextMaxDistance = 0;
    while (i < nums.size()) {
        // if we are not able to move anymore with this jump
        if (curMaxDistance == 0) {
            // take a jump
            jumps++;
            // set curMaxDistance to nextMaxDistance saved while moving
            curMaxDistance = nextMaxDistance;
            // reset nextMaxDistance
            nextMaxDistance = 0;
        }
        else {
            // decrement the current and next maxDistance because this step needs to be considered for both
            curMaxDistance--;
            nextMaxDistance--;
            // if the current value of nextMaxDistance is less than if we were to jump from here, update nextMaxDistance
            nextMaxDistance = max(nextMaxDistance, nums[i]);
            i++;
        }
    }
    return jumps;
}

int main(int argc, char **argv) {
    vector<int> test = {3, 2, 5, 1, 1, 9, 3, 4};
    std::cout << minJumps(test) << '\n';
    return 0;
}
