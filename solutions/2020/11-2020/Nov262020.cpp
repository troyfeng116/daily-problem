#include <iostream>
#include <vector>
using namespace std;

/*
A fixed point in a list is where the value is equal to its index. So for example the list [-5, 1, 3, 4], 
1 is a fixed point in the list since the index and value is the same. Find a fixed point (there can be many, 
just return 1) in a sorted list of distinct elements, or return None if it doesn't exist.
*/

/* APPROACH 1: Binary search. If arr[m] < m, there can't be a fixed point to the left of m because elements
are distinct. If arr[m] > m, there can't be a fixed point to the right of m. O(N log N) */
int binarySearchAux(vector<int> arr, int l, int r) {
    if (l > r) {
        std::cout << "NONE\n";
        return -1;
    }
    int m = (l+r)/2;
    if (arr[m] < m) return binarySearchAux(arr, m+1, r);
    if (arr[m] > m) return binarySearchAux(arr, l, m-1);
    return m;
}
int findFixedPoint(vector<int> arr) {
    return binarySearchAux(arr, 0, arr.size()-1);
}

int main(int argc, char **argv) {
    vector<int> arr = {-5, 1, 3, 4};
    std::cout << findFixedPoint(arr) << '\n';
    return 0;
}
