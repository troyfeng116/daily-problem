#include <iostream>
#include <vector>
using namespace std;

/*
Given a sorted list of numbers, and two integers low and high representing the lower and upper
bound of a range, return a list of (inclusive) ranges where the numbers are missing. A range
should be represented by a tuple in the format of (lower, upper).
*/

void printPair(pair<int, int> p) {
    std::cout << "[" << p.first << ", " << p.second << "]";
}
void printVector(vector<pair<int, int> > arr) {
    if (arr.size() == 0) {
        std::cout << "[]\n";
        return;
    }
    std::cout << "[";
    for (int i = 0; i < arr.size() - 1; i++) {
        printPair(arr[i]);
        std::cout << ", ";
    }
    printPair(arr[arr.size() - 1]);
    std::cout << "]\n";
}

/* APPROACH 1: Linear scan. O(N) */
vector<pair<int, int> > missingIntervals(vector<int> arr, int l, int r) {
    int intervalStart = l;
    vector<pair<int, int> > ans;
    for (int i = 0; i < arr.size() && arr[i] <= r; i++) {
        if (arr[i] < intervalStart) ;
        else if (arr[i] == intervalStart) intervalStart++;
        else {
            ans.push_back({intervalStart, arr[i] - 1});
            intervalStart = arr[i] + 1;
        }
    }
    if (intervalStart <= r) {
        ans.push_back({intervalStart, r});
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<int> arr = {1, 3, 5, 10};
    int l = -2, r = 10;

    printVector(missingIntervals(arr, l, r));
    return 0;
}
