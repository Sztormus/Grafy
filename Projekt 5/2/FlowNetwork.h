#pragma once

#include <string>
#include "GraphRepresentation.h"
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include "IncidenceMatrix.h"

class FlowNetwork  
{
	friend int expPath(FlowNetwork* net, int* path);

private:
	int nodeNumber = 0;
	int edgeNumber = 0;
	int layerNumber = 0;
	AdjacencyList* adjacencyList = nullptr;
	AdjacencyMatrix* adjacencyMatrix = nullptr;
	IncidenceMatrix* incidenceMatrix = nullptr;
	int (*wages)[3] = nullptr;
	int* layers = nullptr;
	
	int**c = nullptr;
	int**f = nullptr;
	int**cf = nullptr;
	
public:
	FlowNetwork(int N);
	void DrawNetwork(std::string file);
	void DrawFlow(std::string file);
	void FordFulkerson(void);
	~FlowNetwork();
};

