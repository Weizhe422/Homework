#pragma once
#include "Graph.h"
#include <vector>
#include <queue>
#include <algorithm>
#include <climits>
using namespace std;
class DisjointSet {
	vector<int> parent, rank;
public:
	DisjointSet(int n) {
		parent.resize(n);
		rank.resize(n, 0);
		for(int i = 0; i < n; ++i) parent[i] = i;
	}
	int find(int i) {
		if(parent[i] == i) return i;
		return parent[i] = find(parent[i]);
	}
	void unionSets(int i, int j) {
		int root_i = find(i);
		int root_j = find(j);
		if(root_i != root_j) {
			if(rank[root_i] < rank[root_j]) {
				parent[root_i] = root_j;
			} else if(rank[root_i] > rank[root_j]) {
				parent[root_j] = root_i;
			} else {
				parent[root_j] = root_i;
				rank[root_i]++;
			}
		}
	}
};
class WeightedGraph : public Graph {
	vector<vector<pair<int, int>>> adjList;
	struct Edge {
		int u, v, weight;
	};
	vector<Edge> edges;
public:
	WeightedGraph(int v) : Graph(v) {
		adjList.resize(v);
	}
	void insertEdge(int u, int v, int weight) {
		adjList[u].push_back({v, weight});
		adjList[v].push_back({u, weight});
		edges.push_back({u, v, weight});
	}
	void insertEdge(int u, int v) override {
		insertEdge(u, v, 1);
	}
	void display() override {
		for(int i = 0; i < numVertices; ++i) {
			cout << i << ": ";
			for(auto& edge : adjList[i]) {
				cout << "(" << edge.first << ", w:" << edge.second << ") ";
			}
			cout << endl;
		}
	}
	void Prim(int startVertex) {
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
		vector<int> key(numVertices, INT_MAX);
		vector<int> parent(numVertices, -1);
		vector<bool> inMST(numVertices, false);
		pq.push({0, startVertex});
		key[startVertex] = 0;
		while(!pq.empty()) {
			int u = pq.top().second;
			int weight_u = pq.top().first;
			pq.pop();
			if(inMST[u]) continue;
			inMST[u] = true;
			for(auto& edge : adjList[u]) {
				int v = edge.first;
				int weight = edge.second;

				if(!inMST[v] && key[v] > weight) {
					key[v] = weight;
					pq.push({key[v], v});
					parent[v] = u;
				}
			}
		}

		cout << "Prim's MST:\n";
		long long totalWeight = 0;
		for (int i = 0; i < numVertices; ++i) {
			if (parent[i] != -1) {
				cout << parent[i] << " - " << i << " : " << key[i] << "\n";
				totalWeight += key[i];
			}
		}
		cout << "Total Weight: " << totalWeight << endl;
	}
	void Kruskal() {
		vector<Edge> sortedEdges = edges;
		sort(sortedEdges.begin(), sortedEdges.end(), [](const Edge& a, const Edge& b){
			return a.weight < b.weight;
		});
		DisjointSet ds(numVertices);
		vector<Edge> mst;
		long long mstWeight = 0;

		for(auto& edge : sortedEdges) {
			if(ds.find(edge.u) != ds.find(edge.v)) {
				ds.unionSets(edge.u, edge.v);
				mst.push_back(edge);
				mstWeight += edge.weight;
			}
		}
		cout << "Kruskal's MST:\n";
		for (auto& edge : mst) {
			cout << edge.u << " - " << edge.v << " : " << edge.weight << "\n";
		}
		cout << "Total Weight: " << mstWeight << endl;
	}
	void Dijkstra(int src) {
		priority_queue<pair<int, int>, vector<pair<int, int>>, greater<pair<int, int>>> pq;
		vector<int> dist(numVertices, INT_MAX);
		pq.push({0, src});
		dist[src] = 0;
		while(!pq.empty()) {
			int u = pq.top().second;
			int d = pq.top().first;
			pq.pop();
			if (d > dist[u]) continue;
			for(auto& edge : adjList[u]) {
				int v = edge.first;
				int weight = edge.second;
				if(dist[v] > dist[u] + weight) {
					dist[v] = dist[u] + weight;
					pq.push({dist[v], v});
				}
			}
		}

		cout << "Dijkstra's Shortest Paths from " << src << ":\n";
		for(int i = 0; i < numVertices; ++i) {
			cout << "To " << i << " : ";
			if (dist[i] == INT_MAX) cout << "Infinity\n";
			else cout << dist[i] << "\n";
		}
	}
};
