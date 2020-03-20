#include "Digraph.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

Digraph::Digraph(int n, double p): size(n)
{
	srand(time(NULL));
	
	adjacencyMatrix = new AdjacencyMatrix(size);
	adjacencyList = new AdjacencyList(size);
	incidenceMatrix = new IncidenceMatrix(size);
	
	for(int i = 0; i < size; ++i)
	{
		for(int j = 0; j < size; ++j)
		{
			if((rand()/(double)RAND_MAX) < p)
			{
				adjacencyMatrix->setEdge(i, j);
				adjacencyList->setEdge(i, j);
				incidenceMatrix->setEdge(i, j);
			}
		}
	}
	
	for(int i = 0; i < size; ++i)
	{
		for(int j = 0; j < size; ++j)
		{
			if(incidenceMatrix->edgeExists(i, j))
				++edgeNumber;
		}
	}
	
	wages = new int[edgeNumber][3];
	
	int k = 0;
	for(int i = 0; i < size; ++i)
	{
		for(int j = 0; j < size; ++j)
		{
			if(incidenceMatrix->edgeExists(i, j))
			{
				wages[k][0] = i;
				wages[k][1] = j;
				wages[k][2] = rand()%10 + 1;
				++k;
			}
		}
	}
	
	adjacencyMatrix->print();
	adjacencyList->print();
	incidenceMatrix->print();
	
	cout << "Wagi dla poszczegolnych krawedzi:" << endl;
	for(int i = 0; i < edgeNumber; ++i)
	{
		cout << wages[i][0] << "-" << wages[i][1] << ": " << wages[i][2] << endl;
	}
	cout << endl;
}

Digraph::~Digraph()
{
	delete adjacencyList;
	delete adjacencyMatrix;
	delete incidenceMatrix;
	delete[] wages;
}
