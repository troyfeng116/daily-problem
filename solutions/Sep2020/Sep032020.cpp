#include <iostream>
using namespace std;

/*
You are given an array. Each element represents the price of a stock on that 
particular day. Calculate and return the maximum profit you can make from 
buying and selling that stock only once.

For example: [9, 11, 8, 5, 7, 10]

Here, the optimal trade is to buy when the price is 5, and sell when it is 
10, so the return value should be 5 (profit = 10 - 5 = 5).
*/

/* APPROACH 1: Brute force O(N^2) */
int maxProfit(int *prices, int n) {
    int max = 0;
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            max = std::max(prices[j]-prices[i], max);
        }
    }
    return max;
}

/* APPROACH 2: Track min encountered in one pass. O(N) */
int maxProfit2(int *prices, int n) {
    int buy = INT_MAX;
    int ans = 0;
    for (int i = 0; i < n; i++) {
        if (prices[i] < buy) buy = prices[i];
        else ans = std::max(ans, prices[i]-buy);
    }
    return ans;
}
int main(int argc, char **argv) {
    int n = 6;
    int *test = new int[n];
    test[0]=1; test[1]=1100; test[2]=100; test[3]=500; test[4]=7; test[5]=10;
    std::cout << maxProfit(test, n) << '\n';
    std::cout << maxProfit2(test, n) << '\n';
    return 0;
}
