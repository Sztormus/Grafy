#include "pch.h"
#include "DistanceMatrix.h"
#include <iostream>

using namespace std;

DistanceMatrix::DistanceMatrix(int n)
{
	size = n;
	Matrix = new int*[n];
	for (int i = 0; i < n; i++)
	{
		Matrix[i] = new int[n];
	}
	for (int i = 0; i < n; i++)
	{
		for (int j = 0; j < n; j++)
		{
			Matrix[i][j] = -1;
		}
	}
}

DistanceMatrix::~DistanceMatrix()
{
	for (int i = 0; i < size; i++)
	{
		delete Matrix[i];
	}
	delete[] Matrix;
}

void DistanceMatrix::print()
{
	cout << "Macierz odleglosci: \n";
	for (int i = 0; i < size; i++)
	{
		for (int j = 0; j < size; j++)
		{
			if (Matrix[i][j] >= 100)
				cout << Matrix[i][j] << " ";
			else if (Matrix[i][j] >= 10)
				cout << " " << Matrix[i][j] << " ";
			else cout << "  " << Matrix[i][j] << " ";
		}
		cout << endl;
	}
}

void DistanceMatrix::setFromDijkstra(int vertex, int *tracks)
{
	for (int i = 0; i < size; i++)
	{
		if (Matrix[i][vertex] == -1)
			Matrix[i][vertex] = tracks[i];
		if (Matrix[vertex][i] == -1)
			Matrix[vertex][i] = tracks[i];
	}
}

void DistanceMatrix::printCenter()
{
	int* sums = new int[size];
	int min = 1000; 
	for (int i = 0; i < size; i++)
	{
		int sum = 0;
		for (int j = 0; j < size; j++)
		{
			sum += Matrix[i][j];
		}
		sums[i] = sum;
		if (sum < min) min = sum;
	}
	cout << "Centrum grafu:" << endl;
	for (int i = 0; i < size; i++)
	{
		if (sums[i] == min) cout << i << " ";
	}
	cout << endl;

	delete[] sums;
}

void DistanceMatrix::printMinimax()
{
	int* maxes = new int[size];
	int min = 1000;
	for (int i = 0; i < size; i++)
	{
		int max = 0;
		for (int j = 0; j < size; j++)
		{
			if( Matrix[i][j] > max) max = Matrix[i][j];
		}
		maxes[i] = max;
		if (max < min) min = max;
	}

	cout << "Centrum minimax grafu:" << endl;
	for (int i = 0; i < size; i++)
	{
		if (maxes[i] == min) cout << i << " ";
	}
	cout << endl;

	delete[] maxes;
}