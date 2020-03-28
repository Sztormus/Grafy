#pragma once

#include <string>
#include <vector>
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

	int** tempGraph;
	int edgeCounter;

public:
	Graph(std::string input);
	~Graph();
	bool Check();
	void DrawGraph(std::string file);
	void Shuffle(int n);
	void BuildGraph();

	// funkcja sprawdzająca czy krawedz miedzy wierzcholkami u, v jest mostem (po zniszczeniu mostu graf przestalby byc spojny)	
	bool isBridge(int u, int v);
	
	// zwraca liczbe niezniszczonych jeszcze krawedzi w grafie
	int edgeCount();
	
	// wyznaczenie sciezki Eulera
	void findEulerianCircuit(int edgeCounter = 0, int start = 0);

};

// funkcja globalna tworząca ciąg wejściowy do grafu wierzcholkow eulerowskich
std::string eulerianVertices(int n);