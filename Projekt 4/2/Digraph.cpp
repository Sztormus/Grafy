#include "Digraph.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <stack>

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
	
	if(edgeNumber > 0)
	{
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
	}
	
	adjacencyMatrix->print();
	adjacencyList->print();
	incidenceMatrix->print();
	
	if(edgeNumber > 0)
	{
		cout << "Wagi dla poszczegolnych krawedzi:" << endl;
		for(int i = 0; i < edgeNumber; ++i)
		{
			cout << wages[i][0] << "-" << wages[i][1] << ": " << wages[i][2] << endl;
		}
		cout << endl;
	}
}

int* Digraph::Kosaraju()
{
	int* f = new int[size];
	int* d = new int[size];
	int* comp = new int[size];
	int t = 0;
	int nr = 0;
	
	for(int v = 0; v < size; ++v)
	{
		f[v] = -1;
		d[v] = -1;
	}
	
	for(int v = 0; v < size; ++v)
	{
		if(d[v] == -1)
		{
			Visit(v, t, d, f);
		}
	}

	for(int v = 0; v < size; ++v)
		comp[v] = -1;
		
	bool* check = new bool[size];
	stack<int> S;
	int index;
	int value;
	
	for(int v = 0; v < size; ++v)
		check[v] = false;
		
	while(S.size() < size)
	{
		index = -1;
		value = INT_MIN;
		
		for(int i = 0; i < size; ++i)
		{
			if(f[i] > value && check[i] == false)
			{
				value = f[i];
				index = i;
			}
		}
		
		check[index] = true;
		S.push(index);
	}
	
	while(!S.empty())
	{
		int v = S.top();
		S.pop();
		
		if(comp[v] == -1)
		{
			++nr;
			comp[v] = nr;
			Components(nr, v, comp);
		}
	}
	
	delete[] d;
	delete[] f;
	delete[] check;
	
	return comp;
}

void Digraph::Visit(int v, int& t, int* d, int* f)
{
	++t;
	d[v] = t;
			
	for(int u = 0; u < size; ++u)
	{
		if(adjacencyMatrix->edgeExists(v, u))
		{
			if(d[u] == -1)
				Visit(u, t, d, f);
		}
	}
	
	++t;
	f[v] = t;
}

void Digraph::Components(int& nr, int v, int* comp)
{
	for(int u = 0; u < size; ++u)
	{
		if(adjacencyMatrix->edgeExists(u, v))
		{
			if(comp[u] == -1)
			{
				comp[u] = nr;
				Components(nr, u, comp);
			}
		}
	}
}

Digraph::~Digraph()
{
	delete adjacencyList;
	delete adjacencyMatrix;
	delete incidenceMatrix;
	delete[] wages;
}
