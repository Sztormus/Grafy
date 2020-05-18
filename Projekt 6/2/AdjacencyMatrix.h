#pragma once
#include "GraphRepresentation.h"

class AdjacencyMatrix : public GraphRepresentation
{
public:
	AdjacencyMatrix(int n);
	~AdjacencyMatrix();
	void setEdge(int node1, int node2, double wage);
	double getEdge(int node1, int node2);
	bool edgeExists(int node1, int node2);
	void print();
};
