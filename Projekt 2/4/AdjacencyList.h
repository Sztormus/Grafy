#pragma once
#include "GraphRepresentation.h"

class AdjacencyList : public GraphRepresentation
{
public:
	AdjacencyList(int n);
	~AdjacencyList();
	void setEdge(int node1, int node2);
	int edgeExists(int node1, int node2);
	void print();

private:
	int* nodeEdges;
};