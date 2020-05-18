#include <iostream>
#include "AdjacencyMatrix.h"

using namespace std;

AdjacencyMatrix::~AdjacencyMatrix()
{
	for(int i=0; i<nodes; i++)
	{
		delete[] Representation[i];
	}
	delete[] Representation;
}

AdjacencyMatrix::AdjacencyMatrix(int n)
{
	nodes = n;
	edges = 0;
	Representation = new double*[n];
	for (int i = 0; i < n; i++)
	{
		Representation[i] = new double[n];
		for (int j = 0; j < n; j++) Representation[i][j] = 0;
	}
}

void AdjacencyMatrix::setEdge(int node1, int node2, double wage)
{
	if (!basicCheck(node1, node2)) return;

	Representation[node1][node2] = wage;
	Representation[node2][node1] = wage;
	edges++;
}

double AdjacencyMatrix::getEdge(int node1, int node2){
	return Representation[node1][node2];
}

bool AdjacencyMatrix::edgeExists(int node1, int node2)
{
	if (Representation[node1][node2] != 0) return 1;
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