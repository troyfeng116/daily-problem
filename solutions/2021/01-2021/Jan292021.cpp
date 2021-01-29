#include <iostream>
#include <vector>
using namespace std;

/*
Given a list of numbers and a target number n, find 3 numbers in the list that sums closest to the
target number n. There may be multiple ways of creating the sum closest to the target number, you
can return any combination in any order.

ex. list = [2, 1, -5, 4], target = -1 -> -5+1+2 = -2 or -5+1+4 = 0
*/

void print(vector<int> arr) {
    if (arr.size() == 0) {
        cout << "[]\n";
        return;
    }
    cout << "[";
    for (int i = 0; i < arr.size() - 1; i++) {
        cout << arr[i] << ", ";
    }
    cout << arr[arr.size() - 1] << "]\n";
}

/* APPROACH 1: Brute force triple nested loop. O(N^3) */
vector<int> closestTripleSum(vector<int> list, int target) {
    int n = list.size();
    vector<int> ans = {0, 0, 0};
    int closestDist = INT_MAX;
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            for (int k = j + 1; k < n; k++) {
                int dist = list[i] + list[j] + list[k] - target;
                if (abs(dist) < closestDist) {
                    closestDist = abs(dist);
                    ans = {list[i], list[j], list[k]};
                }
            }
        }
    }
    return ans;
}

/* APPROACH 2: Sort the array, fix one element of the triple, and use two pointers for the other
two elements. O(N^2) */
vector<int> closestTripleSum2(vector<int> list, int target) {
    sort(list.begin(), list.end());
    int n = list.size();
    vector<int> ans = {0, 0, 0};
    int closestDist = INT_MAX;
    for (int f = 0; f < n - 2; f++) {
        int l = f + 1, r = n - 1;
        while (l < r) {
            int sum = list[f] + list[l] + list[r];
            if (abs(sum - target) < closestDist) {
                closestDist = abs(sum - target);
                ans = {list[f], list[l], list[r]};
            }
            if (sum > target) r--;
            else l++;
        }
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<int> list = {2, 1, -5, 4};
    int target = -1;

    cout << "APPROACH 1 TESTING: ";
    print(closestTripleSum(list, target));

    cout << "APPROACH 2 TESTING: ";
    print(closestTripleSum2(list, target));
    return 0;
}
