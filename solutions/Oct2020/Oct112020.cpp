#include <iostream>
#include <string>
#include <vector>
using namespace std;

/*
Two words can be 'chained' if the last character of the first word is the same as the first character of 
the second word.

Given a list of words, determine if there is a way to 'chain' all the words in a circle.

Example:
Input: ['eggs', 'karat', 'apple', 'snack', 'tuna']
Output: True
Explanation:
The words in the order of ['apple', 'eggs', 'snack', 'karat', 'tuna'] creates a circle of chained words.
*/

/* QUESTIONS:
-only lowercase alphabetic characters? Will assume yes
*/
#define SIZE 26

void print(vector<string> words) {
    if (words.size() == 0) {
        std::cout << "[]\n";
        return;
    }
    std::cout << "[";
    for (int i = 0; i < words.size()-1; i++) {
        std::cout << words[i] << ", ";
    }
    std::cout << words[words.size()-1] << "]\n";
}

/* APPROACH 1: Backtracking. Runs in O(N^N) exponential */
bool chainableAux(vector<string> words, vector<bool> &used, vector<string> &soFar) {
    int n = words.size();
    if (soFar.size() == n) return soFar[n-1].back() == soFar[0].front();
    string prev = soFar[soFar.size()-1];
    char target = prev.back();
    for (int i = 0; i < words.size(); i++) {
        if (words[i].front() == target && !used[i]) {
            used[i] = true;
            soFar.push_back(words[i]);
            if (chainableAux(words, used, soFar)) return true;
            used[i] = false;
            soFar.pop_back();
        }
    }
    return false;
}
bool chainable(vector<string> words) {
    vector<bool> used(words.size());
    vector<string> soFar;
    bool result = false;
    for (int i = 0; i < words.size(); i++) {
        used[i] = true;
        soFar.push_back(words[i]);
        if (chainableAux(words, used, soFar)) {
            result = true;
            break;
        }
        used[i] = false;
        soFar.pop_back();
    }
    print(soFar);
    return result;
}

/* APPROACH 2: Digraph. Nodes are letters, make edge between first and last letters of each word. Then,
we need for each letter, indegree = outdegree and strongly connected (DFS). O(N) */
void dfs(vector<int> adj[], int u, vector<bool> &visited) {
    visited[u] = true;
    for (int i = 0; i < adj[u].size(); i++) {
        int v = adj[u][i];
        if (!visited[v]) dfs(adj, v, visited);
    }
}
bool isConnected(vector<int> adj[], vector<bool> &mark, int start) {
    vector<bool> visited(SIZE, false);
    dfs(adj, start, visited);
    for (int i = 0; i < SIZE; i++) {
        if (mark[i] && !visited[i]) return false;
    }
    return true;
}
bool chainable2(vector<string> words) {
    vector<int> adj[SIZE];
    vector<bool> mark(SIZE, false);
    vector<int> in(SIZE, 0), out(SIZE, 0);
    for (int i = 0; i < words.size(); i++) {
        int u = words[i].front()-'a';
        int v = words[i].back()-'a';
        mark[u] = true;
        mark[v] = true;
        out[u]++;
        in[v]++;
        adj[u].push_back(v);
    }
    for (int i = 0; i < SIZE; i++) {
        if (in[i] != out[i]) return false;
    }
    return isConnected(adj, mark, words[0].front()-'a');
}

int main(int argc, char **argv) {
    vector<string> words = {"eggs", "karat", "apple", "snack", "tunafish"};
    std::cout << chainable(words) << '\n';
    std::cout << chainable2(words) << '\n';
    return 0;
}
