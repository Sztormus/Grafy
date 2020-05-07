#include "pch.h"
#include <iostream>
#include "AdjacencyMatrix.h"

using namespace std;

AdjacencyMatrix::~AdjacencyMatrix()
{
	for(int i=0; i<nodes; i++)
	{
		delete Representation[i];
	}
	delete Representation;
}

AdjacencyMatrix::AdjacencyMatrix(int n)
{
	nodes = n;
	edges = 0;
	Representation = new int*[n];
	for (int i = 0; i < n; i++)
	{
		Representation[i] = new int[n];
		for (int j = 0; j < n; j++) Representation[i][j] = 0;
	}
}

void AdjacencyMatrix::setEdge(int node1, int node2)
{
	if (!basicCheck(node1, node2)) return;

	Representation[node1][node2] = 1;
	edges++;
}

int AdjacencyMatrix::edgeExists(int node1, int node2)
{
	if (Representation[node1][node2] == 1) return 1;
	else return 0;
}

void AdjacencyMatrix::print()
{
	cout << "-------------------\n";
	cout << "Macierz sasiedztwa:\n";
	for (int i = 0; i < nodes; i++)
	{
		for (int j = 0; j < nodes; j++)
		{
			cout << Representation[i][j] << " ";
		}
		cout << endl;
	}
	cout << "-------------------\n";

}

