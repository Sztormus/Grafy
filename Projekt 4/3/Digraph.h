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
	void Components(int& nr, int v, int* comp, AdjacencyMatrix& Gt);

	bool in_tab(int number, int* tab);
	void setWage(int a, int b);
	int getWage(int a, int b);


public:
	Digraph(int n, double p);
	int* Kosaraju();

	bool Bellman_Ford(int w, int s);	//s-wierzcholek
	void SSS(int* tab, int k);
	~Digraph();
};

int max_num(int *comp, int n);

