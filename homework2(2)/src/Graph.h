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
