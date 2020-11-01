#include <iostream>
#include <unordered_map>
#include <vector>
using namespace std;

/*
Given a list of words, group the words that are anagrams of each other. (An anagram are 
words made up of the same letters).

Example:

Input: ['abc', 'bcd', 'cba', 'cbd', 'efg']
Output: [['abc', 'cba'], ['bcd', 'cbd'], ['efg']]
*/

void print(vector<vector<string> > ans) {
    for (int i = 0; i < ans.size(); i++) {
        std::cout<< "[ ";
        for (int j = 0; j < ans[i].size(); j++) {
            std::cout << ans[i][j] << ' ';
        }
        std::cout << "]\n";
    }
}

/* APPROACH 1: Place anagrams into buckets. Hash by sorted string. O(N) space, O(N*M) time */
string sortString(string str) {
    string copy = str;
    sort(copy.begin(), copy.end());
    return copy;
}
vector<vector<string> > groupAnagrams(vector<string> words) {
    unordered_map<string, vector<string> > table;
    for (int i = 0; i < words.size(); i++) {
        string sorted = sortString(words[i]);
        if (table.count(sorted)) table[sorted].push_back(words[i]);
        else {
            vector<string> list;
            list.push_back(words[i]);
            table.insert({sorted, list});
        }
    }
    vector<vector<string> > ans;
    for (unordered_map<string, vector<string> >::iterator it = table.begin(); it != table.end(); it++) {
        ans.push_back(it->second);
    }
    return ans;
}

int main(int argc, char **argv) {
    vector<string> test;
    test.push_back("abc");
    test.push_back("bcd");
    test.push_back("cba");
    test.push_back("cbd");
    test.push_back("efg");
    vector<vector<string> > res = groupAnagrams(test);
    print(res);
    return 0;
}
