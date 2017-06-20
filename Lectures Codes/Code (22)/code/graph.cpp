/********************************************************
 * File: wiki-graph.cpp
 *
 * Code to play around with the Wikipedia graph.
 */
#include <iostream>
#include <string>
#include <fstream>
#include "set.h"
#include "stack.h"
#include "queue.h"
#include "vector.h"
#include "simpio.h"
#include "console.h"
#include "random.h"
using namespace std;

void makeTestGraph(Map<string, Vector<string> > &map) {
	Vector<string> allNodes;
	for (char ch = 'A'; ch <= 'Z'; ch++) {
		string node = string()+ch;
		allNodes += node;
		map.put(node,Vector<string>());
	}

	for (int i = 0; i < allNodes.size(); i++) {
		for (int j = i+1; 
			j < allNodes.size() && j < i + 3; 
			j++) {
			string node1 = allNodes[i];
			string node2 = allNodes[j];
			map[node1] += node2;
			map[node2] += node1;
		}
	}
}

struct Path {
	string node;
	int pathLength;
	Path() {}
	Path(string s, int i) {
		node = s;
		pathLength = i;
	}
};

void depthFirstSearch(Map<string,Vector<string> > &graph,
					  string startNode) {
	Set<string> visitedNodes;
	Stack<string> toVisit;
	toVisit.push(startNode);
	while(!toVisit.isEmpty()) {
		string nextNode = toVisit.pop();
		if (!visitedNodes.contains(nextNode)) {
			cout << "Visiting: " << nextNode << endl;
			visitedNodes += nextNode;
			foreach(string neighbor in graph[nextNode]) {
				toVisit.push(neighbor);
			}
		} else {
			cout << "Already Visited: " << nextNode << endl;
		}
	}
}

void breadthFirstSearch(Map<string,Vector<string> > &graph,
						string startNode) {
	Set<string> visitedNodes;
	Queue<Path> toVisit;
	Path p(startNode,0);
	toVisit.enqueue(p);
	while (!toVisit.isEmpty()) {
		Path nextPath = toVisit.dequeue();
		if (!visitedNodes.contains(nextPath.node)) {
			cout << "Reached: " << nextPath.node << 
				" Path Length: " << nextPath.pathLength << endl;
			visitedNodes += nextPath.node;
			foreach (string neighbor in graph[nextPath.node]) {
				Path newPath(neighbor,nextPath.pathLength + 1);
				toVisit.enqueue(newPath);
			}
		}
	}
}

int main() {
	Map<string, Vector<string> > graph;
	makeTestGraph(graph);
	string startNode = "A";
	//depthFirstSearch(graph,startNode);
	breadthFirstSearch(graph,startNode);
	return 0;
}
