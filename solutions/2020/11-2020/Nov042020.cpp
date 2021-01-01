#include <iostream>
#include <string>
#include <vector>
#include <queue>
#include <unordered_map>
using namespace std;

/*
Given a non-empty list of words, return the k most frequent words. The output should be sorted from 
highest to lowest frequency, and if two words have the same frequency, the word with lower alphabetical 
order comes first. Input will contain only lower-case letters.

Example:
Input: ["daily", "interview", "pro", "pro", 
"for", "daily", "pro", "problems"], k = 2
Output: ["pro", "daily"]
*/

// Custom compare: first check frequencies (greatest first), then lexicographic order.
bool myCompare(unordered_map<string, int>::iterator a, unordered_map<string, int>::iterator b) {   
    return a->second != b->second ? a->second > b->second : a->first.compare(b->first) < 0;
}

void print(vector<string> arr) {
    std::cout << "[";
    for (int i = 0; i < arr.size()-1; i++) {
        std::cout << arr[i] << ", ";
    }
    std::cout << arr[arr.size()-1] << "]\n";
}

/* APPROACH 1: Bucket sort, sort by bucket size. O(N log N) */
vector<string> kMostFrequent(vector<string> words, int k) {
    int n = words.size();
    unordered_map<string, int> buckets;
    for (int i = 0; i < n; i++) {
        if (buckets.count(words[i]) == 0) buckets[words[i]] = 0;
        else buckets[words[i]]++;
    }
    vector<unordered_map<string, int>::iterator > unique;
    unordered_map<string, int>::iterator itr; 
    for (itr = buckets.begin(); itr != buckets.end(); itr++) {
        unique.push_back(itr);
    }
    sort(unique.begin(), unique.end(), myCompare);
    vector<string> ans;
    for (int i = 0; i < min(n,k); i++) {
        ans.push_back(unique[i]->first);
    }
    return ans;
}

/* APPROACH 2: priority queue. (k,v) = (word, freq); priority by freq and then alphabetical order. */
vector<string> kMostFrequent2(vector<string> words, int k) {
    int n = words.size();
    unordered_map<string, int> buckets;
    for (int i = 0; i < n; i++) {
        if (buckets.count(words[i]) == 0) buckets[words[i]] = 0;
        else buckets[words[i]]++;
    }
    auto comp = [&](string a, string b) {
        return buckets[a] != buckets[b] ? buckets[a] > buckets[b] : a.compare(b) < 0;
    };
    priority_queue<string, vector<string>, decltype(comp)> q(comp);
    for (auto itr = buckets.begin(); itr != buckets.end(); itr++) {
        q.push(itr->first);
        if (q.size() > k) q.pop();
    }
    vector<string> ans;
    while (!q.empty()) {
        ans.push_back(q.top());
        q.pop();
    }
    for (int i = 0; i < k/2; i++) {
        string temp = ans[i];
        ans[i] = ans[k-i-1];
        ans[k-i-1] = temp;
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<string> test = {"daily", "interview", "pro", "pro", "for", "daily", "pro", "problems"};
    int k = 2;

    std::cout << "APPROACH 1 TESTING: ";
    print(kMostFrequent(test, k));

    std::cout << "APPROACH 2 TESTING: ";
    print(kMostFrequent2(test, k));

    return 0;
}
