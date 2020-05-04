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
	int edgeNumber0 = 0;
	// przechowuje nowy index starego wierzcholka
	int* newNodes = nullptr;

	AdjacencyList* adjacencyList = nullptr;
	AdjacencyMatrix* adjacencyMatrix = nullptr;
	IncidenceMatrix* incidenceMatrix = nullptr;
	int (*wages)[3] = nullptr;
	int* ds = nullptr;
	int* ps = nullptr;
	
	Digraph() = default;
	void Visit(int v, int& t, int* d, int* f);
	void Components(int& nr, int v, int* comp, AdjacencyMatrix& Gt);

	bool in_tab(int number, int* tab);
	int getWage(int a, int b);
	bool edgeExists(int** G_prim, int node1, int node2);

	void setWage(int a, int b, int value);
	int** add_s();
	int* Dijkstra(int start);


public:
	Digraph(int n, double p);
	int* Kosaraju();

	bool Bellman_Ford(int** G_prim, int (*wages)[3], int s);
	void selectConnectedGraph(int* tab, int k);

	int** Johnson();
	int getSize(){ return size; }

	~Digraph();

};

int max_num(int *comp, int n);

