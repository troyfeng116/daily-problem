#include <iostream>
#include <vector>
using namespace std;

/*
Given a list of sorted numbers (can be both negative or positive), return the list of numbers
squared in sorted order.

ex. {-5, -3, -1, 0, 1, 4, 5} => {0, 1, 1, 9, 16, 25, 25}
*/

void print(vector<int> arr) {
    std::cout << "[";
    for (int i = 0; i < arr.size()-1; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[arr.size()-1] << "]\n";
}

/* APPROACH 1: Brute force would be to square all the numbers and then sort. O(N log N) */
vector<int> sortSquares(vector<int> arr) {
    int n = arr.size();
    vector<int> squares(n, 0);
    for (int i = 0; i < n; i++) squares[i] = arr[i] * arr[i];
    sort(squares.begin(), squares.end());
    return squares;
}

/* APPROACH 2: Two pointers since arr is sorted. O(N) */
vector<int> sortSquares2(vector<int> arr) {
    int n = arr.size();
    int l = 0, r = n-1;
    vector<int> squares(n, 0);
    for (int index = n-1; index >= 0; index--) {
        if (arr[l] * arr[l] > arr[r] * arr[r]) {
            squares[index] = arr[l] * arr[l];
            l++;
        }
        else {
            squares[index] = arr[r] * arr[r];
            r--;
        }
    }
    return squares;
}

int main(int argc, char **argv) {
    vector<int> arr = {-5, -3, -1, 0, 1, 4, 5};

    std::cout << "APPROACH 1 TESTING: ";
    vector<int> res = sortSquares(arr);
    print(res);

    std::cout << "APPROACH 2 TESTING: ";
    vector<int> res2 = sortSquares2(arr);
    print(res2);
    return 0;
}
