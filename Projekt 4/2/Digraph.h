#pragma once

#include <string>
#include "GraphRepresentation.h"
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include "IncidenceMatrix.h"

class Digraph  
{
private:
	int size = 0;
	int edgeNumber = 0;
	AdjacencyList* adjacencyList = nullptr;
	AdjacencyMatrix* adjacencyMatrix = nullptr;
	IncidenceMatrix* incidenceMatrix = nullptr;
	int (*wages)[3] = nullptr;
	
	Digraph() = default;
	void Visit(int v, int& t, int* d, int* f);
	void Components(int& nr, int v, int* comp);

public:
	Digraph(int n, double p);
	int* Kosaraju();
	~Digraph();
};

