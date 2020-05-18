#pragma once

#include "AdjacencyMatrix.h"
#include <string>

class Graph  
{
private:
	int size = 0;
	int* x_coordinate = nullptr;
	int* y_coordinate = nullptr;
	int* circuit = nullptr;
	int* mixed_circuit = nullptr;
	AdjacencyMatrix* adjacencyMatrix = nullptr;

	// calculates distance between two nodes
	double CalculateWage(int i, int j);
	// calculates sum of the whole circuit distance
	double SumWages(int* circuit);
	// finds first hamilton circuit
	void Hamilton();
	// creates mixed hamilton circuit
	void MixHamilton(int a, int b, int c, int d);
public:
	Graph(std::string input);
	~Graph();
	double Annealing();
	void DrawGraph(std::string file);
};

