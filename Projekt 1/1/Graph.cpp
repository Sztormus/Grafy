#include "Graph.h"
#include <fstream>
#include <iostream>

using namespace std;

Graph::Graph(std::string input)
{
	cout << "Wczytywanie danych z pliku: " << input << endl;
	ifstream wej(input);
	string line, check;
	int n = 0;
	
	getline(wej, line);
	check = line;
	++n;
	getline(wej, line);
	while(line != check && line != "")
	{
		++n;
		check = line;
		getline(wej, line);
	}
	size = n;
	
	wej.close();
	wej.open("input.txt");
	getline(wej, line);
	check = line;
	
	cout << "Reprezentacja grafu: ";
	if(line.find(":") != string::npos)
	{
		cout << "Lista sasiedzwtwa" << endl;
		size_t pos = 0;
		string token;
		string delimiter = " ";
		adjacencyList = new AdjacencyList(size);
		for (int i = 0; i < size; ++i)
		{
			line.erase(0, line.find(":") + 2);
			pos = 0;
			token = "";
			while ((pos = line.find(delimiter)) != string::npos)
			{
				token = line.substr(0, pos);
				adjacencyList->setEdge(i, atoi(token.c_str()));
				line.erase(0, pos + delimiter.length());
			}
			if(line != " ")
			{
				adjacencyList->setEdge(i, atoi(line.c_str()));
			}
			getline(wej, line);
		}
		adjacencyList->print();
	}
	else if(line[0] == '0')
	{
		cout << "Macierz sasiedztwa" << endl;
		adjacencyMatrix = new AdjacencyMatrix(size);
		for(int i = 0; i < size; ++i)
		{
			for(int j = i + 1; j < size; ++j)
			{
				if(line[2 * j] == '1')
				adjacencyMatrix->setEdge(i, j);
			}
			getline(wej, line);
		}
		adjacencyMatrix->print();
	}
	else
	{
		cout << "Macierz incydencji" << endl;
		incidenceMatrix = new IncidenceMatrix(n);
		string* tab = new string[size];
		tab[0] = line;
		for(int i = 1; i < size; ++i)
		{
			getline(wej, line);
			tab[i] = line;
		}
		
		for(int i = 0; i < tab[0].length(); ++i)
		{
			for(int j = 0; j < size; ++j)
			{
				if(tab[j][i] == '1')
				{
					for(int k = j + 1; k < size; ++k)
					{
						if(tab[k][i] == '1')
						{
							incidenceMatrix->setEdge(k, j);
							break;
						}
					}
					break;
				}
			}
		}
		delete[] tab;
		incidenceMatrix->print();
	}
	wej.close();
	cout << "Pozostale dwie reprezentacje:" << endl;
	if(adjacencyMatrix != nullptr)
	{
		adjacencyList = new AdjacencyList(size);
		incidenceMatrix = new IncidenceMatrix(size);
		
		for(int i = 0; i < size; ++i)
		{
			for(int j = 0; j < size; ++j)
			{
				if(adjacencyMatrix->edgeExists(i, j))
				{
					adjacencyList->setEdge(i, j);
					incidenceMatrix->setEdge(i, j);
				}
			}
		}
		
		adjacencyList->print();
		incidenceMatrix->print();
	}
	else if(adjacencyList != nullptr)
	{
		adjacencyMatrix = new AdjacencyMatrix(size);
		incidenceMatrix = new IncidenceMatrix(size);
		
		for(int i = 0; i < size; ++i)
		{
			for(int j = 0; j < size; ++j)
			{
				if(adjacencyList->edgeExists(i, j))
				{
					adjacencyMatrix->setEdge(i, j);
					incidenceMatrix->setEdge(i, j);
				}
			}
		}
		
		adjacencyMatrix->print();
		incidenceMatrix->print();
	}
	else
	{
		adjacencyList = new AdjacencyList(size);
		adjacencyMatrix = new AdjacencyMatrix(size);
		
		for(int i = 0; i < size; ++i)
		{
			for(int j = 0; j < size; ++j)
			{
				if(incidenceMatrix->edgeExists(i, j))
				{
					adjacencyMatrix->setEdge(i, j);
					adjacencyList->setEdge(i, j);
				}
			}
		}
		
		adjacencyMatrix->print();
		adjacencyList->print();
	}
}

Graph::~Graph()
{
	delete adjacencyList;
	delete adjacencyMatrix;
	delete incidenceMatrix;
}

void Graph::DrawGraph()
{
	ofstream wyj("graph.dot");
	
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
	
	cout << "Wygenerowano skrypt o nazwie 'graph.dot' dla grafu o liczbie wierzcholkow: " << size << endl;
	wyj.close();
}
