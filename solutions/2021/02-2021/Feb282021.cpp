#include <iostream>
using namespace std;

/*
A Perfect Number is a positive integer that is equal to the sum of all its positive divisors
except itself. Write a function to determine if a number is a perfect number.

ex.
28 = 1 + 2 + 4 + 7 + 14
*/

/* APPROACH 1: Loop from 1 to sqrt(n) and keep track of sum. O(sqrt(N)) */
bool isPerfect(int n) {
    int sum = 1;
    for (int i = 2; i <= floor(sqrt(n)); i++) {
        if (n % i == 0) {
            sum += i;
            if (n / i != i) sum += n / i;
        }
    }
    return sum == n;
}

int main(int argc, char **argv) {
    int n1 = 28;
    int n2 = 27;
    cout << isPerfect(n1) << " " << isPerfect(n2) << '\n';
    return 0;
}
