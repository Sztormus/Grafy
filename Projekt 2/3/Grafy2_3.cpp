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
	while (true)
	{
		cout << "Podaj ciag: ";
		getline(cin, input);
		if (input == "q")
			break;

		Graph graph(input);
	
		if (graph.Check())
		{
			cout << "Podany ciag jest ciagiem graficznym." << endl;
			graph.BuildGraph();
			cout << "Okreslamy najwieksza spojna skladowa." << endl;
			int nr = 0;								
			int * comp = Components(&graph, &nr);
			int* elements = new int[nr];
			int max = 0;

			for (int i = 1; i <= nr; i++)
			{
				int sum = 0;
				cout << i << ": ";
				for (int j = 0; j < graph.size; j++)
				{
					if (comp[j] == i)
					{
						cout << j + 1 << ", ";
						sum++;
					}
				}
				cout << endl;
				elements[i - 1] = sum;
				if (sum > max)
				{
					max = sum;
				}
			}

			cout << endl << "Najwieksza(e) spojna(e) skladowa(e): ";
			for (int i = 1; i <= nr; i++)
			{
				if (elements[i-1] == max)
					cout << i << ", ";
			}
			cout << endl;
			graph.DrawGraph("output.dot");
		}
		else
		{
			cout << "Podany ciag nie jest ciagiem graficznym. Koniec." << endl;
		}
	}
}

int* Components(Graph* g, int* nr)
{
	//iloc wierzcholkow
	int el = g->size;			
	int *comp = new int[el];
	for (int i = 0; i < el; i++)
	{
		//elementy nie naleza jeszcze do skladowych
		comp[i] = -1;
	}	
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


