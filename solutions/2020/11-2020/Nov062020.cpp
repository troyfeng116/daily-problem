#include <iostream>
#include <string>
#include <stack>
#include <vector>
using namespace std;

/*
Given a file path with folder names, '..' (Parent directory), and '.' (Current directory), return the shortest 
possible file path (Eliminate all the '..' and '.').

Example
Input: '/Users/Joma/Documents/../Desktop/./../'
Output: '/Users/Joma/'
*/

/* QUESTION: answer is either at or subdirectoy of pwd ( . ) ?
Will assume no: if outside root, I'll return / */

/* APPROACH 1: Stack. Split string by / character and navigate around. Return remaining content in stack
joined by '/'. O(N) space + time */
vector<string> split(string str, string delim) {
    vector<string> ans;
    char *cStr = &str[0];
    char *cDelim = &delim[0];
    char *token = strtok(cStr, cDelim);
    while (token != NULL) {
        ans.push_back(token);
        token = strtok(NULL, cDelim);
    }
    return ans;
}
string getShortestFilePath(string path) {
    vector<string> arr = split(path, "/");
    stack<string> s;
    for (int i = 0; i < arr.size(); i++) {
        if (arr[i].compare("..") == 0) {
            if (!s.empty()) s.pop();
        }
        else if (arr[i].compare(".") == 0) ;
        else s.push(arr[i]);
    }
    stack<string> rev;
    while (!s.empty()) {
        rev.push(s.top());
        s.pop();
    }
    string ans = "/";
    while (!rev.empty()) {
        ans.append(rev.top());
        rev.pop();
        ans.append("/");
    }
    return ans;
}

int main(int argc, char **argv) {
    string test = "/Users/Joma/Documents/../Desktop/./../";
    std::cout << getShortestFilePath(test) << '\n';
    return 0;
}
