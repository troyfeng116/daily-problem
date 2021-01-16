#include <iostream>
#include <vector>
using namespace std;

/*
Given a list of sorted numbers, and two integers k and x, find k closest numbers to the pivot x.
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

/* APPROACH 1: two pointers. Binary search for index m of closest element to x. Set l = m, r = m.
Expand the window based on which side is closer to x. O(k + log(N)) */
int closest(int a, int b, int x) {
    if (abs(a - x) <= abs(b - x)) return a;
    return b;
}
int findClosest(vector<int> sortedList, int x) {
    int n = sortedList.size();
    int l = 0, r = n - 1;
    while (l <= r) {
        int m = (l+r)/2;
        if (x < sortedList[m]) {
            if (m == 0) return 0;
            if (sortedList[m-1] <= x) {
                if (sortedList[m] == closest(sortedList[m], sortedList[m-1], x)) return m;
                return m - 1;
            } else r = m - 1;
        } else if (sortedList[m] < x) {
            if (m == n - 1) return m;
            if (x <= sortedList[m+1]) {
                if (sortedList[m] == closest(sortedList[m], sortedList[m+1], x)) return m;
                return m + 1;
            } else l = m + 1;
        } else return m;
    }
    return l;
}
vector<int> kClosest(vector<int> sortedList, int k, int x) {
    int n = sortedList.size();
    int m = findClosest(sortedList, x);
    int l = m , r = m;
    for (int i = 1; i < k && !(l == 0 && r >= n - 1); i++) {
        if (l == 0) r++;
        else if (r >= n - 1) l--;
        else {
            if (sortedList[l - 1] == closest(sortedList[l - 1], sortedList[r + 1], x)) l--;
            else r++;
        }
    }
    vector<int> ans;
    for (int i = l; i <= r; i++) {
        ans.push_back(sortedList[i]);
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<int> list = {1, 3, 5, 6, 7, 8, 9};
    int k = 3, x = -1;
    vector<int> res = kClosest(list, k, x);
    print(res);
    return 0;
}
