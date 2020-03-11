#pragma once

class Graph
{
private:
	const unsigned int n;
	const unsigned int l;
	const float p;
	int** arr;

public:
	Graph(const unsigned int nodes, const unsigned int lines, const float probability = 1);
	~Graph();
	void generate();
	void generateWithProbability();
	void printGraph();

};

bool searchRow(int arr[], int length, int value);