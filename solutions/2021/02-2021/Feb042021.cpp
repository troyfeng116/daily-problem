#include <iostream>
#include <vector>
using namespace std;

/*
Given a list of numbers, and a target number n, find all unique combinations of a, b, c, d, such that a + b + c + d = n.

ex. 
list = [1, 1, -1, 0, -2, 1, -1], target = 0 -> [[-1, -1, 1, 1], [-2, 0, 1, 1]]
*/

void printArr(vector<int> arr) {
    if (arr.size() == 0) {
        cout << "[]\n";
        return;
    }
    cout << "[";
    for (int i = 0; i < arr.size() - 1; i++) {
        cout << arr[i] << ", ";
    }
    cout << arr.back() << "]";
}
void printQuadruples(vector<vector<int> > list) {
    if (list.size() == 0) {
        cout << "[[]]\n";
        return;
    }
    cout << "[";
    for (int i = 0; i < list.size() - 1; i++) {
        printArr(list[i]);
        cout << ", ";
    }
    printArr(list.back());
    cout << "]\n";
}

/* APPROACH 1: sort list. Iterate over all a, b and use two pointers on remainder of array to search for c
and d. Note that sorting also lets us skip duplicate quadruples.
O(N^3) */
vector<vector<int> > find2Sums(vector<int> list, int target, int start) {
    vector<vector<int> > ans;
    int l = start, r = list.size() - 1;
    while (l < r) {
        int sum = list[l] + list[r];
        if (sum < target || (l != start && list[l] == list[l - 1])) {
            l++;
        } else if (sum > target || (r != list.size() - 1 && list[r] == list[r + 1])) {
            r--;
        } else {
            ans.push_back({ list[l], list[r] });
            l++;
            r--;
        }
    }
    return ans;
}
vector<vector<int> > find4Sums(vector<int> list, int target) {
    int n = list.size();
    sort(list.begin(), list.end());
    vector<vector<int> > ans;
    for (int a = 0; a < n; a++) {
        if (list[a] * 4 > target) break;
        if (a == 0 || list[a - 1] != list[a]) {
            for (int b = a + 1; b < n; b++) {
                if (list[a] + list[b] * 3 > target) break;
                if (b == a + 1 || list[b - 1] != list[b]) {
                    vector<vector<int> > twoSums = find2Sums(list, target - list[a] - list[b], b + 1);
                    for (int i = 0; i < twoSums.size(); i++) {
                        ans.push_back({ list[a], list[b], twoSums[i][0], twoSums[i][1] });
                    }
                }
            }
        }
    }
    return ans;
}

/* APPROACH 2: General recursive k-sum algorithm. O(N^{k - 1}), or O(N^3) for 4-sum. */
vector<vector<int> > findKSums(vector<int> list, int target, int k, int start) {
    vector<vector<int> > ans;
    if (start >= list.size() || list[start] * k > target || list.back() * k < target) return ans;
    if (k == 2) return find2Sums(list, target, start);
    for (int i = start; i < list.size(); i++) {
        if (i == start || list[i] != list[i - 1]) {
            vector<vector<int> > kMinusOneSums = findKSums(list, target - list[i], k - 1, i + 1);
            for (int j = 0; j < kMinusOneSums.size(); j++) {
                vector<int> kSum = {list[i]};
                for (int k = 0; k < kMinusOneSums[j].size(); k++) {
                    kSum.push_back(kMinusOneSums[j][k]);
                }
                ans.push_back(kSum);
            }
        }
    }
    return ans;
}
vector<vector<int> > find4Sums2(vector<int> list, int target) {
    sort(list.begin(), list.end());
    return findKSums(list, target, 4, 0);
}

int main(int argc, char **argv) {
    vector<int> list = {1, 1, -1, 0, -2, 1, -1};
    int target = 0;

    cout << "APPROACH 1 TESTING:\n";
    printQuadruples(find4Sums(list, target));

    cout << "APPROACH 2 TESTING:\n";
    printQuadruples(find4Sums2(list, target));
    return 0;
}
