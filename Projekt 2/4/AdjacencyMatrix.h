#pragma once
#include "GraphRepresentation.h"

class AdjacencyMatrix : public GraphRepresentation
{
public:
	AdjacencyMatrix(int n);
	~AdjacencyMatrix();
	void setEdge(int node1, int node2);
	int edgeExists(int node1, int node2);
	void print();

};