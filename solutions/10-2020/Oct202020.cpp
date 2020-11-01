#include <iostream>
#include <string>
#include <queue>
using namespace std;

/* 
Given a string, rearrange the string so that no character next to each other are the same. If no such 
arrangement is possible, then return None.

Example:
Input: abbccc
Output: cbcbca
*/

/* APPROACH: alphabet only lower case alpha? Will assume yes */

static const int ALPHA_SIZE = 26;

/* APPROACH 1: By pigeonhole principle, we can't have a majority element. Let N = length; we can't
have more than (N+1)/2 of any char. Bucket sort, check majority element, and rearrange buckets. We
need to sort buckets by frequency, and place the most frequent letters first. To ensure we know what
each original letter is, add 0-25 to multiple of 100 (only works assuming only lowercase alpha). Then
to rearrange, start from 1 and place every other starting with most frequent, then go back to zero 
and place the rest provided no majority element.
Assuming constant size alphabet |A|, O(N) time + space.
Else O( |A| (N+log|A|) ) time, O(N+|A|) space. */
void sort(int buckets[], int l, int r) {
    if (l <= r) {
        int splitter = buckets[r];
        int m = l;
        for (int i = l; i < r; i++) {
            if (buckets[i] < splitter) {
                int temp = buckets[i];
                buckets[i] = buckets[m];
                buckets[m] = temp;
                m++;
            }
        }
        buckets[r] = buckets[m];
        buckets[m] = splitter;
        sort(buckets, l, m-1);
        sort(buckets, m+1, r);
    }
}
string rearrange(string str) {
    int n = str.length();
    int buckets[ALPHA_SIZE];
    for (int i = 0; i < ALPHA_SIZE; i++) buckets[i] = i;
    for (int i = 0; i < n; i++) {
        char c = str.at(i);
        buckets[c-'a'] += 100;
    }
    sort(buckets, 0, ALPHA_SIZE-1);
    char *arr = new char[n];
    int t = 1;
    for (int i = 0; i < ALPHA_SIZE; i++) {
        int code = buckets[i];
        int count = code/100;
        char c = (char) ('a'+(code%100));
        if (count > (n+1)/2) return "None";
        for (int j = 0; j < count; j++) {
            if (t >= n) t = 0;
            arr[t] = c;
            t += 2;
        }
    }
    string ans = "";
    for (int i = 0; i < n; i++) ans += arr[i];
    return ans;
}

/* APPROACH 2: Max heap, priority by frequency. We sorted buckets by frequency because if we place
most frequent letter (not previously used) each time (greedy), we will get a solution. Use priority_queue
with struct for (key,value) where key=char, value=frequency. Store previously used char.
O(N log(|A|)) time: N characters to use, log|A| maxHeap insert for each character.
O(|C|) space */
struct QueueNode { 
    int freq;
    char c; 
  
    // < operator overwrite
    bool operator<(const QueueNode &k) const { 
        return freq < k.freq;
    } 
};
string rearrange2(string str) {
    int n = str.length();
    int buckets[ALPHA_SIZE] = {0};
    for (int i = 0; i < n; i++) {
        buckets[str.at(i)-'a']++;
    }

    priority_queue<QueueNode> maxHeap;
    for (char c = 'a'; c <= 'z'; c++) {
        if (buckets[c-'a'] > 0) maxHeap.push(QueueNode{buckets[c-'a'], c});
    }

    string ans = "";
    QueueNode prev {-1, '#'};
    while (!maxHeap.empty()) {
        QueueNode cur = maxHeap.top();
        maxHeap.pop();
        ans += cur.c;
        if (prev.freq > 0) maxHeap.push(prev);
        cur.freq--;
        prev = cur;
    }
    if (ans.length() != n) return "None";
    return ans;
}

int main(int argc, char **argv) {
    string test = "sfffp";
    std::cout << rearrange(test) << '\n';
    std::cout << rearrange2(test) << '\n';
    return 0;
}
