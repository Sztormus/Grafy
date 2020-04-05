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
	AdjacencyList* adjacencyList = nullptr;
	AdjacencyMatrix* adjacencyMatrix = nullptr;
	IncidenceMatrix* incidenceMatrix = nullptr;
	
public:
	Digraph(std::string input);
	void PageRank();
	~Digraph();
};

