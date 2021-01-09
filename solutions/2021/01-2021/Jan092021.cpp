#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
using namespace std;

/*
Given a list of undirected edges which represents a graph, find out the number
of connected components.

ex.
input [(1, 2), (2, 3), (4, 1), (5, 6)] => 2
In the above example, vertices 1, 2, 3, 4 are all connected, and 5, 6 are
connected, and thus there are 2 connected components in the graph above.
*/

class Graph {
    unordered_map<int, unordered_set<int> > adjList;
    void dfs(int v, unordered_set<int> &visited);
public:
    Graph();
    Graph(vector<pair<int, int> > edges);
    void addEdge(int u, int v);
    void print();
    int numConnectedComponents();
};
void Graph::dfs(int v, unordered_set<int> &visited) {
    visited.insert(v);
    for (auto it = adjList[v].begin(); it != adjList[v].end(); it++) {
        if (visited.find(*it) == visited.end()) {
            dfs(*it, visited);
        }
    }
}
Graph::Graph() {}
void Graph::addEdge(int u, int v) {
    adjList[u].insert(v);
    adjList[v].insert(u);
}
Graph::Graph(vector<pair<int, int> > edges) {
    for (pair<int, int> edge : edges) {
        addEdge(edge.first, edge.second);
    }
}
void Graph::print() {
    for (auto it = adjList.begin(); it != adjList.end(); it++) {
        std::cout << it->first << " -> ";
        for (auto it2 = it->second.begin(); it2 != it->second.end(); it2++) {
            std::cout << *it2 << " ";
        }
        std::cout << '\n';
    }
}
int Graph::numConnectedComponents() {
    unordered_set<int> visited;
    int count = 0;
    for (auto it = adjList.begin(); it != adjList.end(); it++) {
        int v = it->first;
        if (visited.find(v) == visited.end()) {
            dfs(v, visited);
            count++;
        }
    }
    return count;
}

/* APPROACH 1: A simple DFS crossing out all visited nodes. O(N) */
int numConnectedComponents(vector<pair<int, int> > edges) {
    Graph graph(edges);
    graph.print();
    return graph.numConnectedComponents();
}

int main(int argc, char **argv) {
    vector<pair<int, int> > edges = {{1, 2}, {2, 3}, {4, 1}, {5, 6}};
    std::cout << numConnectedComponents(edges) << '\n';
    return 0;
}
