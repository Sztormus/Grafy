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
	AdjacencyList* adjacencyList = nullptr;
	AdjacencyMatrix* adjacencyMatrix = nullptr;
	IncidenceMatrix* incidenceMatrix = nullptr;
	
public:
	Graph(std::string input);
	~Graph();
	void DrawGraph();
};

