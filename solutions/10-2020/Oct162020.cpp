#include <iostream>
using namespace std;

/*
The Fibonacci sequence is the integer sequence defined by the recurrence relation: F(n) = F(n-1) + F(n-2), 
where F(0) = 0 and F(1) = 1. In other words, the nth Fibonacci number is the sum of the prior two Fibonacci 
numbers. Below are the first few values of the sequence:

0, 1, 1, 2, 3, 5, 8, 13, 21, 34, 55, 89, 144...

Given a number n, print the n-th Fibonacci Number.
Examples:
Input: n = 3
Output: 2

Input: n = 7
Output: 13
*/

/* APPROACH 1: Store previous two terms and current term. O(N) */
int nthFib(int n) {
    if (n == 0) return 0;
    if (n < 3) return 1;
    int f2 = 0, f1 = 1, fCur = 1;
    int k = 2;
    while (k < n) {
        f2 = f1;
        f1 = fCur;
        fCur = f1 + f2;
        k++;
    }
    return fCur;
}

/* APPROACH 2: Markov chain with ((1,1), (1,0)). Use fast exponentiation with matrix objects.
O(log N). */
typedef struct TwoByTwo *Mat;
struct TwoByTwo {
    int a, b, c, d;
    TwoByTwo() {
        a = 1;
        b = 1;
        c = 1;
        d = 0;
    }
    void print() {
        std::cout << "(" << a << ", " << b << ", " << c << ", " << d << ")\n";
    }
};
Mat multiply(Mat m1, Mat m2) {
    Mat ans = new TwoByTwo();
    ans->a = m1->a * m2->a + m1->b * m2->c;
    ans->b = m1->a * m2->b + m1->b * m2->d;
    ans->c = m1->c * m2->a + m1->d * m2->c;
    ans->d = m1->c * m2->b + m1->d * m2->d;
    return ans;
}
Mat pow(Mat m, int k) {
    if (k == 1) return m;
    Mat half = pow(m, k/2);
    (*half).print();
    Mat result = multiply(half, half);
    return k%2 == 0 ? result : multiply(result, m);
}
int nthFib2(int n) {
    if (n == 0) return 0;
    if (n < 3) return 1;
    Mat base = new TwoByTwo();
    Mat ans = pow(base, n-1);
    return ans->a;
}

/* APPROACH 3: Binet's. O(1), if we take pow O(1) */
int nthFib3(int n) {
    double root5 = sqrtf(5);
    std::cout << root5 << '\n';
    double x = (1 + root5)/2;
    double y = (1 - root5)/2;
    return (int) ((pow(x, n) - pow(y, n))/root5);
}

int main(int argc, char **argv) {
    std::cout << nthFib(12) << '\n';
    std::cout << nthFib2(12) << '\n';
    std::cout << nthFib3(12) << '\n';
    return 0;
}
