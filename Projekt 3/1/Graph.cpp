#include "Graph.h"
#include <fstream>
#include <iostream>
#include <vector>
#include <sstream>
#include <iterator>
#include <algorithm>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <stack>

using namespace std;

Graph::Graph(int n): size(n)
{
	srand(time(NULL));
	
	series = new int[size];
	wages = new int[(size * (size - 1))/2][3];
	
	for(int i = 0; i < (size * (size - 1))/2; ++i)
	{
		wages[i][0] = -1;
		wages[i][1] = -1;
		wages[i][2] = -1;
	}
	
	while(true)
	{
		while(true)
		{
			for(int i = 0; i < size; ++i)
			{
				series[i] = (rand()%(size - 1)) + 1;
			}
		
			if(Check())
			{
				break;
			}
		}
		
		BuildGraph();
		
		if(Consistent())
		{
			break;
		}
	}
	
	cout << "Ciag graficzny: " << endl;
	for(int i = 0; i < size; ++i)
		cout << series[i] << " ";
	cout << endl;
	
	adjacencyMatrix->print();
	adjacencyList->print();
	incidenceMatrix->print();
	
	int k = 0;
	for(int i = 0; i < size; ++i)
	{
		for(int j = i + 1; j < size; ++j)
		{
			if(adjacencyMatrix->edgeExists(i, j))
			{
				wages[k][0] = i;
				wages[k][1] = j;
				wages[k][2] = rand()%10 + 1;
				++k;
			}
		}
	}
	
	cout << "Wagi dla poszczegolnych krawedzi:" << endl;
	for(int i = 0; i < k; ++i)
	{
		cout << wages[i][0] << "-" << wages[i][1] << ": " << wages[i][2] << endl;
	}
	cout << endl;
}

bool Graph::Consistent()
{
	bool* visited = new bool[size];
	int vc = 0;
	
	stack<int> stack;
	
	for(int i = 0; i < size; ++i)
	{
		visited[i] = false;
	}
	
	stack.push(0);
	visited[0] = true;
	while(stack.empty() == false)
	{
		int v = stack.top();
		stack.pop();
		++vc;
		for(int i = 0; i < size; ++i)
		{
			if(adjacencyMatrix->edgeExists(i, v))
			{
				if(visited[i])
					continue;
				else
				{
					visited[i] = true;
					stack.push(i);
				}
			}
		}
	}
	
	delete[] visited;
	
	if(vc == size)
		return true;
		
	return false;
}

bool Graph::Check()
{
	int* tab = new int[size];
	bool check = true;
	
	for(int i = 0; i < size; ++i)
		tab[i] = series[i];
	
	sort(tab, tab + size, [](int i, int j) {return i > j;});
	
	while(true)
	{
		check = true;
		for(int i = 0; i < size; ++i)
		{
			if(tab[i] != 0)
			{
				check = false;
				break;
			}
		}
		
		if(check)
		{
			delete[] tab;
			return true;
		}
		
		if(tab[0] < 0 || tab[0] >= size)
		{
			delete[] tab;
			return false;
		}
		
		for(int i = 1; i < size; ++i)
		{
			if(tab[i] < 0)
			{
				delete[] tab;
				return false;
			}
		}
		
		for(int i = 1; i <= tab[0]; ++i)
			tab[i] = tab[i] - 1;
			
		tab[0] = 0;
		sort(tab, tab + size, [](int i, int j) {return (i > j);});
	}
}

void Graph::BuildGraph()
{	
	int* tab = new int[size];
	int flag = 0;
	int node = 0;
	int index = 0;
	bool check = true;
	
	adjacencyList = new AdjacencyList(size);
	adjacencyMatrix = new AdjacencyMatrix(size);
	incidenceMatrix = new IncidenceMatrix(size);
	
	for(int i = 0; i < size; ++i)
		tab[i] = series[i];
		
	while(true)
	{
		check = true;
		index = 0;
		for(int i = 0; i < size; ++i)
		{
			if(tab[index] < tab[i])
				index = i;
		}
		
		while(tab[index] > 0)
		{
			node = rand()%size;
			if(node != index && tab[node] > 0 && !adjacencyMatrix->edgeExists(index, node))
			{
				flag = 0;
				adjacencyMatrix->setEdge(node, index);
				adjacencyList->setEdge(node, index);
				incidenceMatrix->setEdge(node, index);
				--tab[node];
				--tab[index];
			}
			else
			{
				++flag;
				if(flag > size * size)
				{
					delete adjacencyList;
					delete adjacencyMatrix;
					delete incidenceMatrix;
					
					BuildGraph();
					
					return;
				}
			}
		}
		
		for(int i = 0; i < size; ++i)
		{
			if(tab[i] != 0)
				check = false;
		}
		
		if(check)
			break;
	}
	
	delete[] tab;
}

void Graph::DrawGraph(std::string file)
{
	ofstream wyj(file);
	
	wyj << "digraph G" << endl << "{" << endl;
	wyj << "	layout=\"circo\";" << endl;
	wyj << "	node [shape = circle];" << endl;
	
	for(int i = 0; i < size - 1; ++i)
		wyj << "	N" << i << " -> N" << i + 1 << " [arrowhead=none][style=invis]" << endl;
	wyj << "	N" << size - 1 << " -> N0 [arrowhead=none][style=invis]" << endl;
	
	for(int i = 0; i < size; ++i)
	{
		for(int j = i + 1; j < size; ++j)
		{
			if(adjacencyMatrix->edgeExists(i, j))
				wyj << "	N" << j << " -> N" << i << " [arrowhead=none]" << endl;
		}
	}
	wyj << "}";
	
	cout << "Wygenerowano skrypt o nazwie '" << file << "' dla grafu o liczbie wierzcholkow: " << size << endl;
	
	wyj.close();
}

Graph::~Graph()
{
	delete adjacencyList;
	delete adjacencyMatrix;
	delete incidenceMatrix;
	delete[] series;
	delete[] wages;
}
