#pragma once

#include <string>
#include "GraphRepresentation.h"
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include "IncidenceMatrix.h"

class Graph  
{
private:
	int size = 0;
	int* series = nullptr;
	AdjacencyList* adjacencyList = nullptr;
	AdjacencyMatrix* adjacencyMatrix = nullptr;
	IncidenceMatrix* incidenceMatrix = nullptr;
	int (*wages)[3] = nullptr;
	
	bool Check();
	void BuildGraph();
	bool Consistent();
	
public:
	Graph(int n);
	~Graph();
	void DrawGraph(std::string file);
};

