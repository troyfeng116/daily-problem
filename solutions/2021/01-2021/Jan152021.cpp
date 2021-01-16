#include <iostream>
#include <vector>
#include <stack>
using namespace std;

/*
Given a list of numbers, for each element find the next element that is larger than the current element. Return the answer as
a list of indices. If there are no elements larger than the current element, then use -1 instead.

ex. {3, 2, 5, 6, 9, 8} => {2, 2, 3, 4, -1, -1}
*/

/*
QUESTIONS:
-duplicates? Will assume yes
*/

void print(vector<int> list) {
    if (list.size() == 0) {
        std::cout << "[]\n";
        return;
    }
    std::cout << "[";
    for (int i = 0; i < list.size() - 1; i++) {
        std::cout << list[i] << ", ";
    }
    std::cout << list[list.size() - 1] << "]\n";
}

/* APPROACH 1: Simple nested loop. O(N^2) */
vector<int> nextLargerIndices(vector<int> list) {
    int n = list.size();
    vector<int> ans(n, -1);
    for (int i = 0; i < n; i++) {
        int j = i+1;
        while (j < n && list[j] <= list[i]) j++;
        if (j < n) ans[i] = j;
    }
    return ans;
}

/* APPROACH 2: Stack. Traverse right to left, and keep indices of local maxim in stack. O(N) time + space */
vector<int> nextLargerIndices2(vector<int> list) {
    int n = list.size();
    stack<int> stk;
    vector<int> ans(n, -1);
    for (int i = n - 1; i >= 0; i--) {
        while (!stk.empty() && list[stk.top()] <= list[i]) {
            stk.pop();
        }
        if (!stk.empty()) {
            ans[i] = stk.top();
        }
        stk.push(i);
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<int> list = {3, 2, 5, 6, 9, 8};

    std::cout << "APPROACH 1 TESTING: ";
    print(nextLargerIndices(list));

    std::cout << "APPROACH 2 TESTING: ";
    print(nextLargerIndices2(list));
    return 0;
}
