#include <iostream>
#include <unordered_map>
#include <vector>
#include <string>
#include <queue>
using namespace std;

/*
You are given a hash table where the key is a course code, and the value is a list of all the 
course codes that are prerequisites for the key. Return a valid ordering in which we can complete 
the courses. If no such ordering exists, return NULL.

Example:
{
  'CSC300': ['CSC100', 'CSC200'], 
  'CSC200': ['CSC100'], 
  'CSC100': []
}

This input should return the order that we need to take these courses:
 ['CSC100', 'CSC200', 
 'CSCS300']
*/

/* 
APPROACH 1: Create digraph and run topSort. We're given a reverse adjacency list, pretty much. 
For each node with indegree zero, add it to topSort list and remove it and its outbound edges.
Finally, reverse result (since adj list was reverse edges)
*/
vector<string> findOrder(unordered_map<string,vector<string> > courses) {
	/* Initialize indegrees */
	unordered_map<string,int> indegree;
	for (auto i = courses.begin(); i != courses.end(); i++) {
		if (indegree.count(i->first)==0) indegree[i->first] = 0;
		for (int j = 0; j < i->second.size(); j++) {
			int count = indegree.count(i->second[j])==0? 0 : indegree[i->second[j]];
			indegree[i->second[j]] = count+1;
		}
	}
	/* Topological sort using queue */
	queue<string> q;
	for (auto i = indegree.begin(); i != indegree.end(); i++) {
		if (i->second == 0) q.push(i->first);
	}
	vector<string> ans;
	while (!q.empty()) {
		string node = q.front();
		q.pop();
		ans.push_back(node);
		for (int i = 0; i < courses[node].size(); i++) {
			string v = courses[node][i];
			indegree[v]--;
			if (indegree[v] == 0) q.push(v);
		}
	}
	/* If still indegree != 0, return NULL. */
	for (auto i = indegree.begin(); i != indegree.end(); i++) {
		if (i->second > 0) {
			std::cout << "CYCLE\n";
			vector<string> null;
			return null;
		}
	}
	/* Reverse and return topSort result */
	std::reverse(ans.begin(),ans.end());
	return ans;
}

int main(int argc, char **argv) {
	unordered_map<string, vector<string> > test;
	vector<string> p1;
	p1.push_back("CSC100"); p1.push_back("CSC200");
	test.emplace("CSC300", p1);
	vector<string> p2;
	p2.push_back("CSC100");
	test.emplace("CSC200", p2);
	vector<string> p3;
	test.emplace("CSC100", p3);
	vector<string> result = findOrder(test);
	for (int i = 0; i < result.size(); i++) std::cout << result[i] << ' ';
	std::cout << '\n';
	return 0;
}
