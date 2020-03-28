#pragma once

#include <string>
#include "GraphRepresentation.h"
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include "IncidenceMatrix.h"
#include "DistanceMatrix.h"

class Graph
{
private:
	int size = 0;
	int* series = nullptr;
	int center = -1;
	int minimax = -1;
	AdjacencyList* adjacencyList = nullptr;
	AdjacencyMatrix* adjacencyMatrix = nullptr;
	IncidenceMatrix* incidenceMatrix = nullptr;
	DistanceMatrix* distanceMatrix = nullptr;
	int(*wages)[3] = nullptr;

	bool Check();
	void BuildGraph();
	bool Consistent();

public:
	Graph(int n);
	~Graph();
	void DrawGraph(std::string file);
	int* Dijkstra(int start);
	void setDistanceMatrix();
	
};

