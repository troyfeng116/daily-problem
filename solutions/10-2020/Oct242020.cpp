#include <iostream>
#include <vector>
using namespace std;

/*
You are given an array of integers. Return all the permutations of this array.
*/

/* QUESTION: print or return? Will assume return */

void print(vector<vector<int> > arr) {
    for (int i = 0; i < arr.size(); i++) {
        std::cout << "[";
        for (int j = 0; j < arr[i].size()-1; j++) {
            std::cout << arr[i][j] << ", ";
        }
        std::cout << arr[i][arr[i].size()-1] << "]\n";
    }
}

/* APPROACH 1: First sort, then generate in lexicographic order. Generating next permutation is O(N) and
assuming distinct, there are N! permutations. So O(N*N!) time and space */
bool nextPermutation(vector<int> &arr) {
    int n = arr.size();
    int k = n-2;
    while (k >= 0 && arr[k] >= arr[k+1]) k--;
    if (k < 0) return false;
    int l = n-1;
    while (arr[l] <= arr[k]) l--;
    int temp = arr[l];
    arr[l] = arr[k];
    arr[k] = temp;
    for (int i = k+1; i <= (n+k)/2; i++) {
        int temp = arr[n-i+k];
        arr[n-i+k] = arr[i];
        arr[i] = temp;
    }
    return true;
}
vector<vector<int> > generatePermutations(vector<int> &arr) {
    sort(arr.begin(), arr.end());
    vector<vector<int> > permutations;
    permutations.push_back(vector<int>(arr));
    while (nextPermutation(arr)) {
        permutations.push_back(vector<int>(arr));
    }
    return permutations;
}

int main(int argc, char **argv) {
    vector<int> test = {2,3,1,4};
    vector<vector<int> > result = generatePermutations(test);
    print(result);
    return 0;
}