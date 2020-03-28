#pragma once

#include <string>
#include "GraphRepresentation.h"
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include "IncidenceMatrix.h"

class FlowNetwork  
{
private:
	int nodeNumber = 0;
	int edgeNumber = 0;
	int layerNumber = 0;
	AdjacencyList* adjacencyList = nullptr;
	AdjacencyMatrix* adjacencyMatrix = nullptr;
	IncidenceMatrix* incidenceMatrix = nullptr;
	int (*wages)[3] = nullptr;
	int* layers = nullptr;
	
public:
	FlowNetwork(int N);
	void DrawNetwork(std::string file);
	~FlowNetwork();
};

