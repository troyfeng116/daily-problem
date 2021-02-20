#include <iostream>
#include <unordered_map>
#include <unordered_set>
#include <vector>
#include <queue>
using namespace std;

/*
Given a node in a connected directional graph, create a copy of the graph.
*/

class Node {
private:
    void printNeighbors() {
        if (neighbors.size() == 0) {
            cout << "[]\n";
            return;
        }
        cout << "[";
        for (int i = 0; i < neighbors.size() - 1; i++) {
            cout << neighbors[i]->val << ", ";
        }
        cout << neighbors.back()->val << "]\n";
    }
    void printDFS(unordered_set<Node*> &visited) {
        cout << val << ": ";
        printNeighbors();
        for (int i = 0; i < neighbors.size(); i++) {
            if (visited.find(neighbors[i]) == visited.end()) {
                visited.insert(neighbors[i]);
                (*neighbors[i]).printDFS(visited);
            }
        }
    }
public:
    int val;
    vector<Node*> neighbors;
    Node() {
        val = 0;
        vector<Node*> adj;
        neighbors = adj;
    }
    Node(int v) {
        val = v;
        vector<Node*> adj;
        neighbors = adj;
    }
    Node(int v, vector<Node*> n) {
        val = v;
        neighbors = n;
    }
    void printGraph() {
        unordered_set<Node*> visited;
        visited.insert(this);
        printDFS(visited);
    }
};

/* APPROACH 1: BFS with visited set. O(N) */
Node *copyGraph(Node *node) {
    if (node == NULL) return NULL;
    Node *copy = new Node(node->val);
    unordered_map<Node*, Node*> map;
    map[node] = copy;
    queue<Node*> q;
    q.push(node);
    while (!q.empty()) {
        Node *cur = q.front();
        q.pop();
        Node *curCopy = map[cur];
        for (int i = 0; i < cur->neighbors.size(); i++) {
            Node *neighbor = cur->neighbors[i];
            if (map.find(neighbor) == map.end()) {
                Node *neighborCopy = new Node(neighbor->val);
                curCopy->neighbors.push_back(neighborCopy);
                map[neighbor] = neighborCopy;
                q.push(neighbor);
            } else {
                curCopy->neighbors.push_back(map[neighbor]);
            }
        }
    }
    return map[node];
}

int main(int argc, char **argv) {
    Node *n1 = new Node(1);
    Node *n2 = new Node(2);
    Node *n3 = new Node(3);
    Node *n4 = new Node(4);
    Node *n5 = new Node(5);
    n1->neighbors.push_back(n5);
    n2->neighbors.push_back(n4);
    n3->neighbors.push_back(n4);
    n4->neighbors.push_back(n2);
    n4->neighbors.push_back(n3);
    n5->neighbors.push_back(n3);
    
    Node *copy = copyGraph(n1);
    copy->printGraph();
    return 0;
}
