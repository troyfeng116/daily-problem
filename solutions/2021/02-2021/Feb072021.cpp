#include <iostream>
#include <vector>
#include <unordered_set>
#include <string>
using namespace std;

/*
Given a list of numbers and a target number, find all possible unique subsets of the list of numbers that sum up
to the target number. The numbers will all be positive numbers.

ex.
list = [10, 1, 2, 7, 6, 1, 5], target = 8 -> [(2, 6), (1, 1, 6), (1, 2, 5), (1, 7)]
*/

void printArr(vector<int> arr) {
    if (arr.size() == 0) {
        cout << "[]";
        return;
    }
    cout << "[";
    for (int i = 0; i < arr.size() - 1; i++) {
        cout << arr[i] << ", ";
    }
    cout << arr.back() << "]";
}
void printListOfArr(vector<vector<int> > list) {
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
vector<int> stringToArr(string s) {
    vector<int> ans;
    int num = 0;
    for (int i = 0; i < s.length(); i++) {
        if (s.at(i) == ',') {
            ans.push_back(num);
            num = 0;
        } else {
            num = num * 10 + s.at(i) - '0';
        }
    }
    return ans;
}

/* APPROACH 1: DFS + backtracking. */
void dfs(vector<int> list, int target, int i, string curPath, unordered_set<string> &ans) {
    if (target == 0) {
        ans.insert(curPath);
        return;
    }
    if (i >= list.size() || target < 0) return;
    dfs(list, target, i + 1, curPath, ans);
    dfs(list, target - list[i], i + 1, curPath + to_string(list[i]) + ',', ans);
}
vector<vector<int> > findTargetSumSubsets(vector<int> list, int target) {
    sort(list.begin(), list.end());
    unordered_set<string> ansSet;
    dfs(list, target, 0, "", ansSet);
    vector<vector<int> > ans;
    for (unordered_set<string>::iterator it = ansSet.begin(); it != ansSet.end(); it++) {
        ans.push_back(stringToArr(*it));
    }
    return ans;
}

/* APPROACH 2: DP. dp[i][j] stores whether there is a subset of list[0, i] that adds to j. Then, walk backwards
recursively from dp[n - 1][target] to find the actual subsets. To guarantee uniqueness, sort list and hash paths
in set. */
void constructPaths(vector<int> list, int target, int i, string curPath, vector<vector<bool> > dp, unordered_set<string> &ans) {
    if (i == 0 && target == 0) {
        ans.insert(curPath);
        return;
    }
    if (i == 0 && dp[0][target]) {
        ans.insert(curPath + to_string(list[i]) + ',');
        return;
    }
    if (dp[i - 1][target]) {
        constructPaths(list, target, i - 1, curPath, dp, ans);
    }
    if (target - list[i] >= 0 && dp[i - 1][target - list[i]]) {
        constructPaths(list, target - list[i], i - 1, curPath + to_string(list[i]) + ',', dp, ans);
    }
}
vector<vector<int> > findTargetSumSubsets2(vector<int> list, int target) {
    sort(list.begin(), list.end());
    int n = list.size();
    vector<vector<bool> > dp(n, vector<bool>(target + 1, false));
    for (int i = 0; i < n; i++) dp[i][0] = true;
    if (list[0] <= target) {
        dp[0][list[0]] = true;
    }
    for (int i = 1; i < n; i++) {
        for (int k = 1; k <= target; k++) {
            if (dp[i - 1][k]) dp[i][k] = true;
            else if (k - list[i] >= 0) {
                dp[i][k] = dp[i - 1][k - list[i]];
            }
        }
    }
    if (!dp[n - 1][target]) return {};
    unordered_set<string> ansSet;
    constructPaths(list, target, n - 1, "", dp, ansSet);
    vector<vector<int> > ans;
    for (unordered_set<string>::iterator it = ansSet.begin(); it != ansSet.end(); it++) {
        ans.push_back(stringToArr(*it));
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<int> list = {10, 1, 2, 7, 6, 1, 5};
    int target = 8;

    cout << "APPROACH 1 TESTING:\n";
    printListOfArr(findTargetSumSubsets(list, target));

    cout << "APPROACH 2 TESTING:\n";
    printListOfArr(findTargetSumSubsets2(list, target));
    return 0;
}