# 41343134 
# 41343143

## 作業二 Graph

## 解題說明
 本作業目標為透過程式實作與操作，理解圖（Graph）在資料結構中的表示方式與常用演算法   
- 圖的表示方式(ADT):

  Adjacency List（鄰接串列）、Adjacency Matrix（鄰接矩陣）
 
- 圖的走訪（DFS、BFS）

  DFS（Depth First Search）：深度優先搜尋，使用遞迴或 stack。

  BFS（Breadth First Search）：廣度優先搜尋，使用 queue。

- 連通元件（Connected Components）

  對每個未被訪問的頂點進行 DFS，DFS 被啟動的次數即為連通元件數量。

- 最小生成樹（Minimum Spanning Tree）
 
  Kruskal 演算法：將邊依權重排序，利用 DSU（Union-Find）避免形成 cycle。

- 最短路徑（Shortest Path）

  Dijkstra 演算法：用 priority queue 每次取出目前距離最小的點進行鬆弛（relax），適用於非負權重圖。


### 解題策略


   
## 程式實作
### IDE:
Microsoft Visual Studio Code C/C++

Graph.h
```cpp
#pragma once
#include <iostream>
using namespace std;
class Graph {
protected:
	int numVertices;
public:
	Graph(int v) : numVertices(v) {}
	virtual ~Graph() = default;
	virtual void insertEdge(int u, int v) = 0;
	virtual void display() = 0;
};


```

LinkedGraph.h
```cpp
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
```

WeightedGraph.h 

```cpp
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


```
main.cpp
```cpp

#include <iostream>
#include "LinkedGraph.h"
#include "WeightedGraph.h"
using namespace std;
int main() {
    cout << "=== LinkedGraph ===\n";
    LinkedGraph lg(5);
    lg.insertEdge(0, 3);
    lg.insertEdge(0, 4);
    lg.insertEdge(1, 2);
    lg.insertEdge(1, 3);

    lg.display();
    lg.DFS(0);
    lg.BFS(0);
    lg.ConnectedComponents();

    cout << "\n=== WeightedGraph ===\n";
    WeightedGraph wg(4);
    wg.insertEdge(0, 1, 12);
    wg.insertEdge(0, 2, 7);
    wg.insertEdge(0, 3, 9);
    wg.insertEdge(1, 3, 14);
    wg.insertEdge(2, 3, 3);

    wg.display();
    cout << endl;
    wg.Prim(0);
    cout << endl;
    wg.Kruskal();
    cout << endl;
    wg.Dijkstra(0);

    return 0;
}

```

## 效能分析

## 測試與驗證

### 測試案例 

| 測試案例 | 輸入參數   | 預期輸出 | 實際輸出 |
|----------|--------------|----------|----------|
| 測試一   |5<br>5 3 1 8 6   | 1 5 3 8 6     |  1 5 3 8 6        |
| 測試二   |6<br>8 5 4 3 2 1   | 1 3 2 8 4 5     |  1 3 2 8 4 5        |
| 測試三   |11<br>5 3 6 1 9 8 2 4 11 7 10   | 1 3 2 4 7 8 6 5 11 9 10     | 1 3 2 4 7 8 6 5 11 9 10       |



### 測試輸入
```

```
### 測試輸出
```

```
### 結論


## 申論及開發報告
