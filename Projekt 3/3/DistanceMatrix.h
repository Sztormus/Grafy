#pragma once

class DistanceMatrix
{
private:
	int ** Matrix;
	int size;

public:
	DistanceMatrix(int n);
	~DistanceMatrix();
	void print();
	void setFromDijkstra(int vertex, int *tracks);

	void printCenter();
	void printMinimax();
};
