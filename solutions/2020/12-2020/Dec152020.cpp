#include <iostream>
#include <vector>
using namespace std;

/*
Given a list of numbers and an integer k, partition/sort the list such that the all numbers less 
than k occur before k, and all numbers greater than k occur after the number k.
*/

void print(vector<int> list) {
    std::cout << "[";
    for (int i = 0; i < list.size()-1; i++) {
        std::cout << list[i] << ", ";
    }
    std::cout << list[list.size()-1] << "]\n";
}

/* APPROACH 1: two vectors for each half, concatenate at the end. O(N) time + space, stable */
vector<int> partition(vector<int> list, int k) {
    vector<int> l, r;
    for (int i = 0; i < list.size(); i++) {
        if (list[i] < k) l.push_back(list[i]);
        else r.push_back(list[i]);
    }
    for (int i = 0; i < r.size(); i++) {
        l.push_back(r[i]);
    }
    return l;
}

/* APPROACH 2: qSort partition. O(N) time + O(1) space, in place, not stable */
void partition2(vector<int> &list, int k) {
    int m = 0;
    for (int i = 0; i < list.size(); i++) {
        if (list[i] < k) {
            int temp = list[i];
            list[i] = list[m];
            list[m] = temp;
            m++;
        }
    }
}

int main(int argc, char **argv) {
    vector<int> list = {2, 2, 2, 5, 2, 2, 2, 2, 5};
    int k = 3;

    vector<int> res = partition(list, k);
    std::cout << "APPROACH 1 TESTING: ";
    print(res);

    partition2(list, k);
    std::cout << "APPROACH 1 TESTING: ";
    print(list);
    return 0;
}
