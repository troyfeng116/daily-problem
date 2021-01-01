#include <iostream>
#include <vector>
using namespace std;

/*
Given a directed graph, reverse the directed graph so all directed edges are reversed.

Example:
Input:
A -> B, B -> C, A -> C

Output:
B -> A, C -> B, C -> A
*/

/* 
QUESTIONS: 
-what is graph input format? Will do once for adj matrix and one for adj list.
-what is graph output format? Will match graph input format
*/

/* APPROACH 1 (adj matrix): Transpose of graph is transpose of matrix. O(V^2) */
void printAdjMat(vector<vector<bool> > adj) {
    for (int u = 0; u < adj.size(); u++) {
        for (int v = 0; v < adj[u].size(); v++) {
            std::cout << adj[u][v] << " ";
        }
        std::cout << "\n";
    }
}
vector<vector<bool> > reverseDiGraphAdjMat(vector<vector<bool> > adj) {
    int n = adj.size();
    vector<vector<bool> > transpose = vector<vector<bool> >(n, vector<bool>(n, 0));
    for (int i = 0; i < n; i++) {
        for (int j = i+1; j < n; j++) {
            transpose[i][j] = adj[j][i];
            transpose[j][i] = adj[i][j];
        }
    }
    return transpose;
}

/* APPROACH 2 (adj list): Traverse graph. For each (u,v), add (v,u) to reversed. O(V+E). */
void printAdjList(vector<vector<int> > adj) {
    for (int u = 0; u < adj.size(); u++) {
        std::cout << u << " -> ";
        for (int v = 0; v < adj[u].size(); v++) {
            std::cout << v << " ";
        }
        std::cout << "\n";
    }
}
vector<vector<int> > reverseDiGraphAdjList(vector<vector<int> > adj) {
    int n = adj.size();
    vector<vector<int> > res = vector<vector<int> >(n, vector<int>());
    for (int u = 0; u < n; u++) {
        for (int j = 0; j < adj[u].size(); j++) {
            int v = adj[u][j];
            res[v].push_back(u);
        }
    }
    return res;
}

int main(int argc, char **argv) {
    // APPROACH 1 TESTING
    vector<vector<bool> > adjMat = {
        {0, 1, 1},
        {0, 0, 1},
        {0, 0, 0},
    };
    std::cout << "APPROACH 1 (adj matrix) TESTING: \n";
    printAdjMat(reverseDiGraphAdjMat(adjMat));

    // APPROACH 2 TESTING
    vector<vector<int> > adjList = {
        {1,2},
        {2},
        {},
    };
    std::cout << "APPROACH 2 (adj list) TESTING: \n";
    printAdjList(reverseDiGraphAdjList(adjList));
    return 0;
}
