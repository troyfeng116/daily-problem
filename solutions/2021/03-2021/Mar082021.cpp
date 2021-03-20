#include <iostream>
#include <vector>
using namespace std;

/*
Given an array containing only positive integers, return if you can pick two integers from the array
which cuts the array into three pieces such that the sum of elements in all pieces is equal.

ex.
array = [2, 4, 5, 3, 3, 9, 2, 2, 2]
=> true
choosing 5 and 9 results in three pieces [2, 4], [3, 3] and [2, 2, 2]. Sum = 6.

ex.
array = [1, 1, 1, 1],
=> false
*/

/* APPROACH 1: Two pointers (similar to 3/6). Make sure left and right sums are equal, then check middle
part by subtracting from total sum. If lSum < rSum, increment lPointer. Elif lSum > rSum, decrement
rPointer. Else check middle sum. O(N) */
bool canPartitionAroundTwoElements(vector<int> arr) {
    int n = arr.size();
    if (n < 5) return false;
    int totalSum = 0;
    for (int i = 0; i < n; i++) {
        totalSum += arr[i];
    }
    int lSum = arr[0], rSum= arr[n - 1];
    int l = 1, r = n - 2;
    while (l + 1 < r) {
        if (lSum < rSum) {
            lSum += arr[l];
            l++;
        } else if (lSum > rSum) {
            rSum += arr[r];
            r--;
        } else if (totalSum - lSum - rSum - arr[l] - arr[r] == lSum) {
            cout << "Pick " << arr[l] << " and " << arr[r] << ": sum = " << lSum << '\n';
            return true;
        } else {
            lSum += arr[l];
            rSum += arr[r];
            l++;
            r--;
        }
    }
    return false;
}

int main(int argc, char **argv) {
    vector<int> test = {2, 4, 5, 3, 3, 9, 2, 2, 2};
    cout << canPartitionAroundTwoElements(test) << '\n';
    return 0;
}
