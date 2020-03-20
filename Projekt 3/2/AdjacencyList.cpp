#include <iostream>
#include <cstdlib>
#include "AdjacencyList.h"

using namespace std;

AdjacencyList::~AdjacencyList()
{
	delete nodeEdges;
	for (int i = 0; i < nodes; i++)
	{
		if (nodeEdges[i] > 0)
			delete Representation[i];
	}
	delete Representation;
}

AdjacencyList::AdjacencyList(int n)
{
	//lista wierzcholkow
	nodes = n;
	edges = 0;
	Representation = new int*[n];
	
	//nodeEdges[i] przedstawia ilosc krawedzi wychodzacych z wierzcholka (dlugosc tablicy)
	nodeEdges = new int[n];
	for (int i = 0; i < n; i++)
	{
		nodeEdges[i] = 0;
	}
}

void AdjacencyList::setEdge(int n1, int n2)
{
	//warunki poczatkowe
	if (!basicCheck(n1, n2)) return;
		
	//w przypadku gdy wezel nie ma jeszcze krawedzi
		if(nodeEdges[n1] == 0)
		{
			Representation[n1] = new int[1];
			Representation[n1][0] = n2;
			nodeEdges[n1]++;
		}
		//gdy wezel ma juz krawedz
		else
		{
			//stworz nowa tablice dlugosci o 1 wiekszej niz ilosc elementow biezacych
			int * newArray = new int[nodeEdges[n1]+1];
			for(int i=0; i<nodeEdges[n1]; i++)
			{
				newArray[i] = Representation[n1][i];
			}
			newArray[nodeEdges[n1]] = n2;
			delete Representation[n1];
			Representation[n1] = new int[nodeEdges[n1]+1];
			Representation[n1] = newArray;
			nodeEdges[n1]++;
		}

		if(nodeEdges[n2] == 0)
		{
			Representation[n2] = new int[1];
			Representation[n2][0] = n1;
			nodeEdges[n2]++;
		}

		else
		{
			int * newArray = new int[nodeEdges[n2]+1];
			for(int i=0; i<nodeEdges[n2]; i++)
			{
				newArray[i] = Representation[n2][i];
			}
			newArray[nodeEdges[n2]] = n1;
			delete Representation[n2];
			Representation[n2] = new int[nodeEdges[n2]+1];
			Representation[n2] = newArray;
			nodeEdges[n2]++;
		}
		edges++;

}

int AdjacencyList::edgeExists(int node1, int node2)
{
	if(nodeEdges[node1] == 0) return 0;
	else
	{
		for(int i=0; i<nodeEdges[node1]; i++)
		{
			if(Representation[node1][i] == node2) return 1;
		}
		return 0;
	}
}

void AdjacencyList::print()
{
	cout << "-------------------\n";
	cout << "Lista sasiedztwa:\n";
	for(int i=0; i<nodes; i++)
	{
		cout <<i <<": ";
		if (nodeEdges[i] == 0)
		{
			cout << "-\n";
			continue;
		}
		else
			for(int j=0; j<nodeEdges[i]; j++)
			{
				cout << Representation[i][j] << " ";
			}
		cout << endl;

	}
	cout << "-------------------\n";
	

}
