// Grafy2_3.cpp : Ten plik zawiera funkcję „main”. W nim rozpoczyna się i kończy wykonywanie programu.
//

#include "pch.h"
#include <iostream>
#include <list>
#include <iterator>
#include <fstream>
#include "Graph.h"

using namespace std;

int* Components(Graph* g, int* nr);
void Components_r(int nr, int v, Graph* g, int** comp);

int main()
{
	string input;
	cout << "Podaj ciag: ";
	getline(cin, input);

	Graph graph(input);
	if (graph.Check())
	{
		cout << "Podany ciag jest ciagiem graficznym." << endl;
		graph.BuildGraph();
		cout << "Okreslamy najwieksza spojna skladowa." << endl;
		int nr = 0;
		int * comp = Components(&graph, &nr);
		int max = 0;

		for (int i = 1; i <= nr; i++)
		{
			int sum = 0;
			cout << nr << ": ";
			for (int j = 0; j < graph.size; j++)
			{
				if (comp[j] == nr)
				{
					cout << j+1 << ", ";
					sum++;
				}
			}
			cout << endl;
			if (sum > max) max = nr;
		}
		cout << endl << "Najwieksza spojna skladowa ma numer " << max << endl;

	}
	else
	{
		cout << "Podany ciag nie jest ciagiem graficznym. Koniec." << endl;
	}
}

int* Components(Graph* g, int* nr)
{
	int el = g->size;
	int *comp = new int[el];
	for (int i = 0; i < el; i++)
	{
		comp[i] = -1;
	}
	//elementy nie naleza jeszcze do skladowych
	//dla kazdego wierzcholka w grafie
	for (int v = 0; v < el; v++)
	{
		if (comp[v] == -1)
		{
			(*nr)++;
			comp[v] = *nr;
			Components_r(*nr, v, g, &comp);
		}
	}
	return comp;
}

void Components_r(int nr, int v, Graph* g, int** comp)
{
	//warunek zakonczenia rekurencji
	int flag = 0;
	for (int i = 0; i < g->size; i++)
	{
		if ((*comp)[i] == -1)
		{
			flag = 1;
			break;
		}
	}
	if (flag == 0) return;

	for (int u = 0; u < g->size; u++)
	{
		if ((g->adjacencyMatrix)->edgeExists(u, v))
		{
			if ((*comp)[u] == -1)
			{
				(*comp)[u] = nr;
				Components_r(nr, u, g, comp);
			}
		}
	}
}


