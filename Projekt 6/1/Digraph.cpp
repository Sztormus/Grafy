#include "Digraph.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>

using namespace std;

Digraph::Digraph(std::string input)
{
	cout << "Wczytywanie danych z pliku: " << input << endl;
	ifstream wej(input);
	string line, check;
	int n = 0;

	getline(wej, line);
	check = line;
	++n;
	getline(wej, line);
	while (line != check && line != "")
	{
		++n;
		check = line;
		getline(wej, line);
	}
	size = n;

	wej.close();
	wej.open("input.txt");

	size_t pos = 0;
	string token;
	string delimiter = " ";
	adjacencyList = new AdjacencyList(size);
	for (int i = 0; i < size; ++i)
	{
		getline(wej, line);
		line.erase(0, line.find(":") + 2);
		pos = 0;
		token = "";
		while ((pos = line.find(delimiter)) != -1)
		{
			token = line.substr(0, pos);
			adjacencyList->setEdge(i, atoi(token.c_str()));
			line.erase(0, pos + delimiter.length());
		}
		if(line != " ")
		{
			adjacencyList->setEdge(i, atoi(line.c_str()));
		}
	}
	adjacencyList->print();

	adjacencyMatrix = new AdjacencyMatrix(size);
	incidenceMatrix = new IncidenceMatrix(size);

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (adjacencyList->edgeExists(i, j))
			{
				adjacencyMatrix->setEdge(i, j);
				incidenceMatrix->setEdge(i, j);
			}
		}
	}

	adjacencyMatrix->print();
	incidenceMatrix->print();
}

void Digraph::PageRank()
{
	srand(time(NULL));
	double d = 0.15;
	int N = 1000000;
	double random = 0;
	int u = 0;
	int v = 0;
	double* visited;
	visited = new double[size];
	for (int i = 0; i < size; ++i)
		visited[i] = 0;

	cout << "Bladzenie przypadkowe:" << endl;

	for (int i = 0; i < N; ++i)
	{
		random = (double)rand()/RAND_MAX;
		if (random > d)
		{
			while (true)
			{
				v = rand() % size;
				if (adjacencyList->edgeExists(u, v) == 1)
				{
					u = v;
					visited[u] += 1;
					break;
				}
			}
		}
		else
		{
			u = rand() % size;
			visited[u] += 1;
		}
	}

	for (int i = 0; i < size; ++i)
	{
		cout << i << " ==> PageRank = " << visited[i] / N << endl;
	}

	delete[] visited;

	cout << endl << "Metoda iteracji wektora obsadzen:" << endl;

	double** P;
	double* output = new double[size];
	double* p0 = new double[size];
	double* p = new double[size];
	double sum;
	for (int i = 0; i < size; ++i)
	{
		output[i] = 0.0;
		p0[i] = 1.0 / size;
		p[i] = 1.0 / size;
	}

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
		{
			if (i == j)
				continue;
			else if(adjacencyMatrix->edgeExists(i, j) == 1)
				output[i] += 1;
		}
	}

	P = new double* [size];

	for (int i = 0; i < size; ++i)
		P[i] = new double[size];

	for (int i = 0; i < size; ++i)
	{
		for (int j = 0; j < size; ++j)
			P[i][j] = (1 - d) * (adjacencyMatrix->edgeExists(i, j) / output[i]) + d / size;
	}

	for (int it = 0; it < N; ++it)
	{
		for (int i = 0; i < size; ++i)
		{
			sum = 0;
			for (int j = 0; j < size; ++j)
				sum += P[j][i] * p0[j];
			p[i] = sum;
		}

		for (int i = 0; i < size; ++i)
			p0[i] = p[i];
	}

	for (int i = 0; i < size; ++i)
	{
		cout << i << " ==> PageRank = " << p[i] << endl;
	}

	delete[] p;
	delete[] p0;
	delete[] output;
	for (int i = 0; i < size; ++i)
		delete[] P[i];
	delete[] P;
}

Digraph::~Digraph()
{
	delete adjacencyList;
	delete adjacencyMatrix;
	delete incidenceMatrix;
}
