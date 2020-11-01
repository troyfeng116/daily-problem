#include <iostream>
#include <vector>
using namespace std;

/*
You are the manager of a number of employees who all sit in a row. The CEO would like to 
give bonuses to all of your employees, but since the company did not perform so well this 
year the CEO would like to keep the bonuses to a minimum.

The rules of giving bonuses is that:
- Each employee begins with a bonus factor of 1x.
- For each employee, if they perform better than the person sitting next to them, the 
employee is given +1 higher bonus (and up to +2 if they perform better than both people 
to their sides).

Given a list of employee's performance, find the bonuses each employee should get.

Example:
Input: [1, 2, 3, 2, 3, 5, 1]
Output: [1, 2, 3, 1, 2, 3, 1]
*/

void print(vector<int> arr) {
    std::cout << "[";
    for (int i = 0; i < arr.size()-1; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[arr.size()-1] << "]\n";
}

/* APPROACH 1: one pass. O(N) */
vector<int> getBonuses(vector<int> performance) {
    int n = performance.size();
    vector<int> ans(n, 1);
    if (n <= 1) return ans;
    if (performance[0] > performance[1]) ans[0]++;
    if (performance[n-1] > performance[n-2]) ans[n-1]++;
    for (int i = 1; i < n-1; i++) {
        if (performance[i] > performance[i-1]) ans[i]++;
        if (performance[i] > performance[i+1]) ans[i]++;
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<int> performance = {1, 2, 3, 2, 3, 5, 1};
    vector<int> bonuses = getBonuses(performance);
    print(bonuses);
    return 0;
}
