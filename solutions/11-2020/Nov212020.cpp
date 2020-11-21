#include <iostream>
#include <vector>
using namespace std;

/*
Kaprekar's Constant is the number 6174. This number is special because it has the property where for 
any 4-digit number that has 2 or more unique digits, if you repeatedly apply a certain function it 
always reaches the number 6174.

This certain function is as follows:
- Order the number in ascending form and descending form to create 2 numbers.
- Pad the descending number with zeros until it is 4 digits in length.
- Subtract the ascending number from the descending number.
- Repeat.

Given a number n, find the number of times the function needs to be applied to reach Kaprekar's 
constant.

ex.
input: n=123
output: 3
3210 - 0123 = 3087
8730 - 0378 = 8352
8352 - 2358 = 6174
*/

#define KAPREKAR_CONSTANT 6174

/* APPROACH 1: Just run the process, assuming number is not repdigit. */
int sortNumber(int n) {
    vector<int> buckets(10, 0);
    while (n != 0) {
        buckets[n%10]++;
        n /= 10;
    }
    int ans = 0;
    for (int i = 0; i < 10; i++) {
        while (buckets[i] > 0) {
            ans *= 10;
            ans += i;
            buckets[i]--;
        }
    }
    return ans;
}
int reverse(int n) {
    int ans = 0;
    while (n != 0) {
        ans *= 10;
        ans += n%10;
        n /= 10;
    }
    return ans;
}
int lengthKaprekarPath(int num) {
    if (num == KAPREKAR_CONSTANT) return 0;
    int asc = sortNumber(num);
    int desc = reverse(asc);
    while (desc < 1000) desc *= 10;
    std::cout << desc << " - " << asc << " = " << (desc-asc) << '\n';
    return 1 + lengthKaprekarPath(desc-asc);
}

int main(int argc, char **argv) {
    std::cout << lengthKaprekarPath(123) << '\n';
    return 0;
}
