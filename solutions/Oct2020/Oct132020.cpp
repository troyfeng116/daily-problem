#include <iostream>
#include <vector>
using namespace std;

/*

The h-index is a metric that attempts to measure the productivity and citation impact of the publication of 
a scholar. The definition of the h-index is if a scholar has at least h of their papers cited h times.

Given a list of publications of the number of citations a scholar has, find their h-index.

Example:
Input: [3, 5, 0, 1, 3]
Output: 3
Explanation:
There are 3 publications with 3 or more citations, hence the h-index is 3.
*/

void print(vector<int> arr) {
    std::cout << "[";
    for (int i = 0; i < arr.size()-1; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[arr.size()-1] << "]\n";
}

void sort(vector<int> &arr, int l, int r) {
    if (l < r) {
        int splitter = arr[r];
        int m = l;
        for (int i = l; i < r; i++) {
            if (arr[i] < splitter) {
                int temp = arr[i];
                arr[i] = arr[m];
                arr[m] = temp;
                m++;
            }
        }
        arr[r] = arr[m];
        arr[m] = splitter;
        sort(arr, l, m-1);
        sort(arr, m+1, r);
    }
}

/* APPROACH 1: Sort and linear pass. O(N log N) */
int getHIndex(vector<int> &citations) {
    int n = citations.size();
    if (n == 0) return 0;
    sort(citations, 0, n-1);
    for (int i = 0; i < n; i++) {
        // If (citations[i]) > (num citations greater than citations[i]), return num citations greater.
        int numCitationsGreater = n-i;
        if (citations[i] >= numCitationsGreater) return numCitationsGreater;
    }
    return 0;
}

/* APPROACH 2: Sort and binary search. Note that above after sorting, if (numCitationsGreater <= citations[m]),
the h-index must be to the left ofor equal to m. And if numCitationsGreat > citations[m], h-index must be 
to right of m.
O(N log N) but with additional O(log N) instead of O(N) */
int getHIndex2(vector<int> &citations) {
    int n = citations.size();
    if (n == 0) return 0;
    sort(citations, 0, n-1);
    int l = 0, r = n-1;
    while (l < r) {
        int m = (l+r)/2;
        int numCitationsGreater = n-m;
        if (numCitationsGreater <= citations[m]) r = m;
        else l = m+1;
    }
    if (citations[l] >= n-l) return n-l;
    return 0;
}

/* APPROACH 2: Bucket sort. Let N = #citations. For each citations[i], if citations[i] > N, place it into
N+1'th bucket. Else, place it into citations[i]'th bucket. Essentially, buckets[c] holds the number of
articles with c citations, and buckets[N] holds the number of articles with > N citations. Then single 
reverse pass until #articles > citations.
O(N) space and time */
int getHIndex3(vector<int> &citations) {
    int n = citations.size();
    vector<int> buckets(n+1);
    for (int i = 0; i < n; i++) {
        int c = citations[i];
        if (c > n) buckets[n]++;
        else buckets[c]++;
    }

    // #articles with >= i citations
    int articles = 0;
    for (int i = n; i >= 0; i--) {
        articles += buckets[i];
        if (articles >= i) return i;
    }
    return 0;
}



int main(int argc, char **argv) {
    vector<int> citations = {3,5,0,1,3};
    int result = getHIndex(citations);
    std::cout << result << '\n';

    vector<int> citations2 = {3,5,0,1,3};
    int result2 = getHIndex2(citations2);
    std::cout << result2 << '\n';

    vector<int> citations3 = {3,5,0,1,3};
    int result3 = getHIndex3(citations3);
    std::cout << result3 << '\n';
    return 0;
}
