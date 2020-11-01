#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
You are given two strings, A and B. Return whether A can be shifted some number of times to get B.

Eg. A = abcde, B = cdeab should return true because A can be shifted 3 times to the right to get B. 
A = abc and B= acb should return false.
*/

void print(vector<int> arr) {
    std::cout << "[";
    for (int i = 0; i < arr.size()-1; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[arr.size()-1] <<  "]\n";
}

/* APPROACH 1: Brute force. For each k, check if strings match for rotation by k. O(N^2) time */
bool isShiftedPair(string A, string B) {
    int n = A.length();
    if (B.length() != n) return false;
    if (n == 0) return true;
    for (int k = 0; k < n; k++) {
        bool flag = true;
        for (int i = 0; i < n; i++) {
            if (A.at(i) != B.at((i+k)%n)) {
                flag = false;
                break;
            }
        }
        if (flag) return true;
    }
    return false;
}

#define ALPHA_SIZE 256
#define MOD 1000000007

/* APPROACH 2: If we concat A to itself, all of its rotations are contined in that string. So if (A+A)
contains B as a substring we return true. O(N) space, O(N) time with Rabin-Karp. */
long powMod(int base, int pow) {
    if (pow == 0) return 1;
    if (pow == 1) return base;
    long half = powMod(base, pow/2);
    long whole = (half * half) % MOD;
    return pow%2 == 0 ? whole : (whole * base) % MOD;
}
long getInitialHash(string s) {
    long hash = 0;
    for (int i = 0; i < s.length(); i++) {
        hash = ((hash*ALPHA_SIZE) + s[i]) % MOD;
    }
    return hash;
}
bool isShiftedPair2(string A, string B) {
    int n = A.length();
    if (B.length() != n) return false;
    if (n == 0) return true;
    if (A.compare(B) == 0) return true;
    string A2 = A+A;
    long patternHash = getInitialHash(B);
    long biggestPrimePow = powMod(ALPHA_SIZE, n-1);
    long textHash = getInitialHash(A);
    for (int l = 1; l <= n; l++) {
        textHash -= biggestPrimePow * A2[l-1];
        textHash *= ALPHA_SIZE;
        int r = l+n-1;
        textHash += A2[r];
        textHash %= MOD;
        if (textHash < 0) textHash += MOD;
        if (patternHash == textHash) {
            if (A2.substr(l, n).compare(B) == 0) return true;
        }
    }
    return false;
}

/* APPROACH 3: Same as Approach 2 but KMP for pattern matching. Also O(N) */
vector<int> getLps(string s) {
    vector<int> lps(s.length());
    lps[0] = 0;
    int len = 0;
    int i = 1;
    while (i < s.size()) {
        if (s[i] == s[len]) {
            len++;
            lps[i] = len;
            i++;
        }
        else {
            if (len != 0) {
                len = lps[len-1];
            }
            else {
                lps[i] = 0;
                i++;
            }
        }
    }
    std::cout << "LPS arr: ";
    print(lps);
    return lps;
}
bool isShiftedPair3(string A, string B) {
    int n = A.length();
    if (B.length() != n) return false;
    if (n == 0) return true;
    if (A.compare(B) == 0) return true;
    // lps[i] = length of longest proper prefix of pattern which is also suffix of pattern[0,i].
    string A2 = A+A;
    vector<int> lps = getLps(B);
    // i = index of A2, j = index of B
    int i = 0, j = 0;
    while (i < 2*n) {
        if (B[j] == A2[i]) {
            i++;
            j++;
        }
        if (j == n) {
            return true;
        }
        else if (i < 2*n && B[j] != A2[i]) {
            if (j != 0) j = lps[j-1];
            else i++;
        }
    }
    return false;
}

int main(int argc, char **argv) {
    string A = "clrwmpkwru";
    string B = "wmpkwruclr";

    std::cout << "APPROACH 1 TESTING:\n";
    std::cout << isShiftedPair(A, B) << '\n';

    std::cout << "APPROACH 2 TESTING:\n";
    std::cout << isShiftedPair2(A, B) << '\n';

    std::cout << "APPROACH 3 TESTING:\n";
    std::cout << isShiftedPair3(A, B) << '\n';

    return 0;
}
