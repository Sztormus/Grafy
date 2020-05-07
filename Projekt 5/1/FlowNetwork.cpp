#include "FlowNetwork.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>

using namespace std;

FlowNetwork::FlowNetwork(int N): layerNumber(N + 2)
{
	bool* check;

	srand(time(NULL));

	layers = new int[layerNumber];

	layers[0] = 1;
	cout << "Warstwa 0: 1 wierzcholek - zrodlo" << endl;
	++nodeNumber;

	for(int i = 1; i < layerNumber - 1; ++i)
	{
		if (layerNumber == 2)
			layers[i] = 2;
		else
			layers[i] = rand() % (N - 1) + 2;
		cout << "Warstwa " << i << ": " << layers[i] << " wierzcholkow" << endl;
		nodeNumber += layers[i];
	}

	layers[layerNumber - 1] = 1;
	cout << "Warstwa " << layerNumber - 1 << ": 1 wierzcholek - ujscie" << endl << endl;
	++nodeNumber;

	cout << "Razem " << nodeNumber << " wierzcholkow" << endl;
	
	adjacencyMatrix = new AdjacencyMatrix(nodeNumber);
	adjacencyList = new AdjacencyList(nodeNumber);
	incidenceMatrix = new IncidenceMatrix(nodeNumber);
	check = new bool[nodeNumber];

	for(int i = 0; i < nodeNumber; ++i)
		check[i] = false;

	check[0] = true;
	for(int i = 1; i < layers[1] + 1; ++i)
	{
		adjacencyList->setEdge(0, i);
		adjacencyMatrix->setEdge(0, i);
		incidenceMatrix->setEdge(0, i);
		check[i] = true;
	}

	check[nodeNumber - 1] = true;
	for(int i = nodeNumber - layers[layerNumber - 2] - 1; i < nodeNumber - 1; ++i)
	{
		adjacencyList->setEdge(i, nodeNumber - 1);
		adjacencyMatrix->setEdge(i, nodeNumber - 1);
		incidenceMatrix->setEdge(i, nodeNumber - 1);
	}

	int bot = 1 + layers[1];
	int top = bot + layers[2];
	int k = 2;
	for(int i = 1; i < nodeNumber - layers[layerNumber - 2] - 1; ++i)
	{
		int random;
		if(i == bot)
		{
			bot = top;
			top += layers[++k];
		}

		random = rand() % (top - bot) + bot;

		adjacencyList->setEdge(i, random);
		adjacencyMatrix->setEdge(i, random);
		incidenceMatrix->setEdge(i, random);

		check[random] = true;
	}

	for(int i = layers[1] + 1; i < nodeNumber - 1; ++i)
	{
		if(!check[i])
		{
			int random;
			bot = layers[0];
			top = bot + layers[1];
			k = 1;

			while(top < i)
			{
				bot = top;
				top += layers[++k];

				if(top > i)
				{
					top -= layers[k];
					bot -= layers[k - 1];
					break;
				}
			}

			random = rand() % (top - bot) + bot;

			adjacencyList->setEdge(random, i);
			adjacencyMatrix->setEdge(random, i);
			incidenceMatrix->setEdge(random, i);

			check[i] = true;
		}
	}

	k = 0;
	
	while (k < 2 * layerNumber)
	{
		int rand1, rand2;

		while (true)
		{
			rand1 = rand() % nodeNumber;
			rand2 = rand() % nodeNumber;

			if (rand1 != rand2 && rand1 != nodeNumber - 1 && rand2 != 0 && !adjacencyMatrix->edgeExists(rand1, rand2) && !adjacencyMatrix->edgeExists(rand2, rand1))
				break;
		}

		adjacencyList->setEdge(rand1, rand2);
		adjacencyMatrix->setEdge(rand1, rand2);
		incidenceMatrix->setEdge(rand1, rand2);

		++k;
	}
	
	for(int i = 0; i < nodeNumber; ++i)
	{
		for(int j = 0; j < nodeNumber; ++j)
		{
			if(incidenceMatrix->edgeExists(i, j))
				++edgeNumber;
		}
	}
	
	if(edgeNumber > 0)
	{
		wages = new int[edgeNumber][3];
	
		int k = 0;
		for(int i = 0; i < nodeNumber; ++i)
		{
			for(int j = 0; j < nodeNumber; ++j)
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

	delete[] check;
}

void FlowNetwork::DrawNetwork(std::string file)
{
	int**c = nullptr;
	c = new int*[nodeNumber];
	for (int i = 0; i < nodeNumber; i++)
		c[i] = new int[nodeNumber];

	for (int i = 0; i < nodeNumber; i++)
		for (int j = 0; j < nodeNumber; j++)
			c[i][j] = 0;

	for (int i = 0; i < edgeNumber; i++)
		c[wages[i][0]][wages[i][1]] = wages[i][2];

	ofstream wyj(file);

	wyj << "digraph G" << endl << "{" << endl;
	wyj << "	node [shape = circle];" << endl;

	for (int i = 0; i < nodeNumber; ++i)
	{
		for (int j = 0; j < nodeNumber; ++j)
		{
			if(i == j)
				continue;
			if(adjacencyMatrix->edgeExists(i, j))
				wyj << "	N" << i << " -> N" << j << " [ label=\"" << c[i][j] << "\"]" << endl;
		}
	}
	wyj << "}";

	cout << "Wygenerowano skrypt o nazwie '" << file << "' dla sieci przeplywow o liczbie wierzcholkow: " << nodeNumber << endl;

	wyj.close();

	for (int i = 0; i < nodeNumber; i++)
		delete[] c[i];
	delete[] c;
}

FlowNetwork::~FlowNetwork()
{
	delete adjacencyList;
	delete adjacencyMatrix;
	delete incidenceMatrix;
	delete[] layers;
	delete[] wages;
}
