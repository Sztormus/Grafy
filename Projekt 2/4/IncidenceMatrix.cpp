#include <iostream>
#include "IncidenceMatrix.h"

using namespace std;

IncidenceMatrix::IncidenceMatrix(int n)
{
	nodes = n;
	edges = 0;
	Representation = new int*[n];
}

IncidenceMatrix::~IncidenceMatrix()
{
	if(edges > 0)
	{
		for (int i = 0; i < nodes; i++)
		{
			delete Representation[i];
		}
	}
	delete Representation;
}

void IncidenceMatrix::setEdge(int n1, int n2)
{
	if (!basicCheck(n1, n2)) return;

	else
	{
		int ** newMatrix;
		newMatrix = new int*[nodes];
		
		//dla pierwszej krawedzi
		if (edges == 0)
		{
			edges++;
			for (int i = 0; i < nodes; i++)
			{
				newMatrix[i] = new int[edges];
				newMatrix[i][0] = 0;
			}
			newMatrix[n1][edges - 1] = 1;
			newMatrix[n2][edges - 1] = 1;
		}
		//dla kazdej kolejnej krawedzi
		else
		{
			edges++;
			for (int i = 0; i < nodes; i++)
			{
				newMatrix[i] = new int[edges];
				for (int j = 0; j < edges - 1; j++)
				{
					newMatrix[i][j] = Representation[i][j];
				}
			}
			for (int i = 0; i < nodes; i++)
			{
				newMatrix[i][edges-1] = 0;
			}
			newMatrix[n1][edges - 1] = 1;
			newMatrix[n2][edges - 1] = 1;
			
		}

		if (edges == 1) //nie utworzylismy wczesniej tablic dla elementow, a wiec wystarczy
			delete Representation;
		else
		{
			for (int i = 0; i < nodes; i++)
			{
				delete Representation[i];
			}
			delete Representation;
		}
		Representation = new int*[nodes];
		Representation = newMatrix;
	}
}

int IncidenceMatrix::edgeExists(int node1, int node2)
{
	for (int i = 0; i < edges; i++)
	{
		if (Representation[node1][i] == 1 && Representation[node2][i] == 1) return 1;
	}
	return 0;
}

void IncidenceMatrix::print()
{
	cout << "-------------------\n";
	cout << "Macierz incydencji: \n";
	for (int i = 0; i < nodes; i++)
	{
		for (int j = 0; j < edges; j++)
		{
			cout << Representation[i][j] << " ";
		}
		cout << endl;
	}
	cout << "-------------------\n";
}

