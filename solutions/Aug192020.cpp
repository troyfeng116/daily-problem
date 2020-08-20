#include <iostream>
#include <vector>
using namespace std;

/*
Given an undirected graph, determine if a cycle exists in the graph.

Can you solve this in linear time, linear space?
*/

/* Following the edge (parent,u) has brought us to this step of dfs. */
bool dfs(vector<vector<int> > adj, int u, int parent, bool *visited) {
	visited[u] = true;
	/* For each edge (u,v) */
	for (int i = 0; i < adj[u].size(); i++) {
		int v = adj[u][i];
		/* If v hasn't been visited, check if it leads to cycle */
		if (!visited[v]) {
			if (dfs(adj,v,u,visited)) return true;
		}
		/* Else, if v has been visited and it wasn't from (parent,u), return true. */
		else if (v != parent) return true;
	}
	return false;
}
bool hasCycle(vector<vector<int> > adj) {
	bool *visited = new bool[adj.size()];
	for (int i = 0; i < adj.size(); i++) {
		visited[i] = false;
	}
	/* For each unvisited node, DFS for cycle. Parent is -1 because this is starting node. */
	for (int u = 0; u < adj.size(); u++) {
		if (!visited[u]) {
			if (dfs(adj, u, -1, visited)) return true;
		}
	}
	return false;
}

void addEdge(vector<vector<int> > *adj, int u, int v) {
	(*adj)[u].push_back(v);
	(*adj)[v].push_back(u);
}

vector<vector<int> > makeGraph(int numNodes) {
	vector<vector<int> > adj;
	for (int i = 0; i < numNodes; i++) {
		vector<int> node;
		adj.push_back(node);
	}
	return adj;
}

int main(int argc, char **argv) {
	vector<vector<int> > adj = makeGraph(5);
	addEdge(&adj, 0,1);
	addEdge(&adj, 1,2);
	addEdge(&adj, 2,3);
	addEdge(&adj, 3,4);
	addEdge(&adj, 4,0);
	std::cout << hasCycle(adj) << '\n';
	return 0;
}
