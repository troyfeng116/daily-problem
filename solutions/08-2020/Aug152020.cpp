#include <iostream>
#include <math.h>
using namespace std;

/*
You are given a positive integer N which represents the number of steps in a staircase. You can either 
climb 1 or 2 steps at a time. Write a function that returns the number of unique ways to climb the stairs.

Can you find a solution in O(n) time?
*/

/*
Let f(n) denote the number of ways to climb n stairs.
f(0) = 1
f(1) = 1
f(2) = 2
f(3) = f(3-1)+f(3-2) = 3
f(4) = f(4-1)+f(4-2) = 5
...
f(n) = f(n-1)+f(n-2)
We can find the n'th Fibonacci number in exponential time recursively, linear time using memoization or
Markov chain, and much faster time using Binet's. Note that for this problem, f(n) is zero-based.
*/

int numWaysRecursive(int n) {
	if (n < 0) return 0;
	if (n <= 1) return 1;
	return numWaysRecursive(n-1) + numWaysRecursive(n-2);
}

int numWaysLinear(int n) {
	if (n <= 1) return 1;
	int n2 = 1; // f(k-2)
	int n1 = 1; // f(k-1)
	int k = 2; // k
	while (k <= n) {
		n1 = n1+n2;
		n2 = n1-n2;
		k++;
	}
	return n1;
}

int binets(int n) {
	double x = (1+sqrt(5))/2;
	double y = (1-sqrt(5))/2;
	return round((pow(x,n+1)+pow(y,n+1))/sqrt(5));
}

int main(int argc, char **argv) {
	std::cout << numWaysRecursive(8) << '\n';
	std::cout << numWaysLinear(8) << '\n';
	std::cout << binets(8) << '\n';
	return 0;
}
