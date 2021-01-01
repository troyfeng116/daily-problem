#include <iostream>
#include <vector>
using namespace std;

/*
You are given an array of integers. Return an array of the same size where the element at 
each index is the product of all the elements in the original array except for the element 
at that index.

For example, an input of [1, 2, 3, 4, 5] should return [120, 60, 40, 30, 24].
*/

void print(vector<int> arr) {
    std::cout << "[";
    for (int i = 0; i < arr.size()-1; i++) std::cout << arr[i] << ",";
    std::cout << arr[arr.size()-1] << "]\n";
}

/* APPROACH 1: Division. O(N) */
vector<int> productAllExcept(vector<int> arr) {
    int prod = 1;
    int numZeroes = 0;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i] == 0) {
            numZeroes++;
        }
        else prod *= arr[i];
    }
    vector<int> ans;
    if (numZeroes > 1) {
        for (int i = 0; i < arr.size(); i++) ans.push_back(0);
    }
    else if (numZeroes == 1) {
        for (int i = 0; i < arr.size(); i++) {
            if (arr[i] == 0) ans.push_back(prod);
            else ans.push_back(0);
        }
    }
    else {
        for (int i = 0; i < arr.size(); i++) {
            ans.push_back(prod/arr[i]);
        }
    }
    return ans;
}

/* APPROACH 2: specs say "you cannot use division in this problem". Can still solve in O(N)
but with extra O(N) space. Store all products up to and after each index, not including
index. ex. for [1,2,3,4,5], left=[1,1,2,6,24] and right=[120,60,20,5, 1]. Then
ans[i]=left[i]*right[i] */
vector<int> productAllExcept2(vector<int> arr) {
    int n = arr.size();
    vector<int> left(n, 0);
    vector<int> right(n, 0);
    left[0] = 1;
    right[n-1] = 1;
    for (int i = 1; i < n; i++) {
        left[i] = left[i-1]*arr[i-1];
        right[n-i-1] = right[n-i]*arr[n-i];
    }
    vector<int> ans;
    for (int i = 0; i < n; i++) {
        ans.push_back(left[i] * right[i]);
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<int> arr = {1,2,3,4,5,6};
    vector<int> res = productAllExcept(arr);
    print(res);
    vector<int> res2 = productAllExcept2(arr);
    print(res2);
    return 0;
}
