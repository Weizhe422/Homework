#pragma once
#include "Graph.h"
#include <vector>
#include <queue>

using namespace std;
class LinkedGraph : public Graph {
	vector<vector<int>> adjList;
	void dfsUtil(int v, vector<bool>& visited) {
		visited[v] = true;
		cout << v << " ";
		for(int neighbor : adjList[v]) {
			if(!visited[neighbor]) {
				dfsUtil(neighbor, visited);
			}
		}
	}
public:
	LinkedGraph(int v) : Graph(v) {
		adjList.resize(v);
	}
	void insertEdge(int u, int v) override {
		adjList[u].push_back(v);
		adjList[v].push_back(u);
	}
	void display() override {
		for(int i = 0; i < numVertices; ++i) {
			cout << i << ": ";
			for(int neighbor : adjList[i]) {
				cout << neighbor << " ";
			}
			cout << endl;
		}
	}

	void DFS(int startVertex) {
		vector<bool> visited(numVertices, false);
		cout << "DFS: ";
		dfsUtil(startVertex, visited);
		cout << endl;
	}
	void BFS(int startVertex) {
		vector<bool> visited(numVertices, false);
		queue<int> q;
		visited[startVertex] = true;
		q.push(startVertex);
		cout << "BFS: ";
		while(!q.empty()) {
			int v = q.front();
			q.pop();
			cout << v << " ";
			for(int neighbor : adjList[v]) {
				if(!visited[neighbor]) {
					visited[neighbor] = true;
					q.push(neighbor);
				}
			}
		}
		cout << endl;
	}

	void ConnectedComponents() {
		vector<bool> visited(numVertices, false);
		int count = 0;
		for(int i = 0; i < numVertices; ++i) {
			if(!visited[i]) {
				cout << "Component " << ++count << ": ";
				dfsUtil(i, visited);
				cout << endl;
			}
		}
	}
};
