#include <iostream>
using namespace std;

/* Happy New Year! */

/*
Given a positive integer, find the square root of the integer without using any built
in square root or power functions (math.sqrt or the ** operator). Give accuracy up to
3 decimal points.
*/

#define EPSILON 0.0001

/* APPROACH 1: Newton-Raphson. f(x) = x^2 - n => f'(x) = 2x. We will approximate
the root to this function, which is sqrt(n) with Newton-Raphson. Let approx = n/2
to start off. Then intersection of tangent line at approx with x-axis is better
approx. Point on line is (approx, f(approx)) and slope is f'(approx). So equation
of tangent line to f(x) at approx is:
y = f(approx) + f'(approx) * (x - approx),
and x-intercept is approx + f(approx) / f'(approx).
Proven to be O(log(n)) */
double mySqrt(int n) {
    double approx = n/2.0;
    while (abs(approx * approx - n) >= EPSILON) {
        approx = approx - (approx * approx - n) / (2 * approx);
    }
    return approx;
}

/* APPROACH 2: Binary search. f(n) = sqrt(n) is a monotone increasing bijective
function, which lets us use binary search. Since 0 <= sqrt(n) <= n, we start
our search bounds at [0, n]. O(log(n)) */
double mySqrt2(int n) {
    double l = 0, r = n, m = n/(2.0);
    while (abs(m * m - n) >= EPSILON) {
        m = (l + r) / 2.0;
        if (n < m * m) {
            r = m;
        } else l = m;
    }
    return m;
}

int main(int argc, char **argv) {
    int n = 5;
    std::cout << "APPROACH 1: " << mySqrt(n) << '\n';
    std::cout << "APPROACH 2: " << mySqrt2(n) << '\n';
    return 0;
}
