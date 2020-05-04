#pragma once
#include "GraphRepresentation.h"

class IncidenceMatrix : public GraphRepresentation
{
public:
	IncidenceMatrix(int n);
	~IncidenceMatrix();
	void setEdge(int node1, int node2);
	int edgeExists(int node1, int node2);
	void print();
	void deleteEdge(int node1, int node2);
	int getRepresentation(int a, int b);

};