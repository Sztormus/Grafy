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
	bool graphic = false;
	int* series = nullptr;
	AdjacencyList* adjacencyList = nullptr;
	AdjacencyMatrix* adjacencyMatrix = nullptr;
	IncidenceMatrix* incidenceMatrix = nullptr;
	
public:
	Graph(std::string input);
	~Graph();
	bool Check();
	void DrawGraph(std::string file);
	void Shuffle(int n);
	void BuildGraph();
};

