#include <iostream>
#include <vector>
using namespace std;

/*
Given a positive integer n, find all primes less than n.
*/

void print(vector<int> arr) {
    if (arr.size() == 0) {
        cout << "[]\n";
        return;
    }
    cout << "[";
    for (int i = 0; i < arr.size() - 1; i++) {
        cout << arr[i] << ", ";
    }
    cout << arr[arr.size() - 1] << "]\n";
}

/* APPROACH 1: Sieve of Eratosthenes. See Project Euler. O(N log(log(N))) */
vector<int> primesLessThan(int n) {
    vector<bool> isPrime(n, true);
    vector<int> primes;
    for (int i = 2; i < n; i++) {
        if (isPrime[i]) {
            primes.push_back(i);
            for (int j = 2 * i; j < n; j += i) {
                isPrime[j] = false;
            }
        }
    }
    return primes;
}

int main(int argc, char **argv) {
    int n = 100;
    print(primesLessThan(n));
    return 0;
}
