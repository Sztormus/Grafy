#include "pch.h"
#include "FlowNetwork.h"
#include <fstream>
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <set>
#include <queue>

using namespace std;

int expPath(FlowNetwork* net, int* path);

FlowNetwork::FlowNetwork(int N): layerNumber(N + 2)
{
	bool* check;

	srand(time(NULL));

	layers = new int[layerNumber];

	layers[0] = 1;
	cout << "Warstwa 0: 1 wierzcholek - zrodlo" << endl;
	++nodeNumber;

	for (int i = 1; i < layerNumber - 1; ++i)
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

	while(k < 2 * layerNumber)
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
		cout << "Przepustowosci dla poszczegolnych krawedzi:" << endl;
		for(int i = 0; i < edgeNumber; ++i)
		{
			cout << wages[i][0] << "-" << wages[i][1] << ": " << wages[i][2] << endl;
		}
		cout << endl;
	}

	delete[] check;

	c = new int*[nodeNumber];
	for (int i = 0; i < nodeNumber; i++)
		c[i] = new int[nodeNumber];

	f = new int*[nodeNumber];
	for (int i = 0; i < nodeNumber; i++)
		f[i] = new int[nodeNumber];

	cf = new int*[nodeNumber];
	for (int i = 0; i < nodeNumber; i++)
		cf[i] = new int[nodeNumber];


	//wiersze to poczatki krawedzi, kolumny to konce
	for (int i = 0; i < nodeNumber; i++)
	{
		for (int j = 0; j < nodeNumber; j++)
		{
			f[i][j] = 0;
			cf[i][j] = 0;
			c[i][j] = 0;
		}
	}

	//przepisuje wartosci z wages do capacity (ulatwienie w dalszej pracy)
	for (int i = 0; i < edgeNumber; i++)
	{
		c[wages[i][0]][wages[i][1]] = wages[i][2];
	}
}

void FlowNetwork::DrawNetwork(std::string file)
{
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
}

void FlowNetwork::DrawFlow(std::string file)
{
	ofstream wyj(file);

	wyj << "digraph G" << endl << "{" << endl;

	for (int i = 0; i < nodeNumber; ++i)
	{
		for (int j = 0; j < nodeNumber; ++j)
		{
			if (i == j)
				continue;
			if (adjacencyMatrix->edgeExists(i, j))
				wyj << "	" << i << " -> " << j << " [ label=\"" << f[i][j] <<"/" << c[i][j] << "\"]" << endl;
		}
	}
	wyj << "}";

	cout << "Wygenerowano skrypt o nazwie '" << file << "' dla sieci przeplywow o liczbie wierzcholkow: " << nodeNumber << endl;

	wyj.close();

}

FlowNetwork::~FlowNetwork()
{
	for (int i = 0; i < nodeNumber; i++)
	{
		delete[] c[i];
		delete[] f[i];
		delete[] cf[i];
	}

	delete[] c;
	delete[] cf;
	delete[] f;

	delete adjacencyList;
	delete adjacencyMatrix;
	delete incidenceMatrix;
	delete[] layers;
	delete[] wages;
}


void FlowNetwork::FordFulkerson(void)
{	
	int* path = new int[nodeNumber];
	int pathLength = 0;

	//tworzê poczatkow¹ siec rezydualna
	for (int i = 0; i < nodeNumber; i++)
	{
		for (int j = 0; j < nodeNumber; j++)
		{
			cf[i][j] = c[i][j];
		}
	}

	while (pathLength = expPath(this, path)) // sciezka istnieje gdy przypisanie zwraca > 0
	{
		int cfp = 1000;
		for (int i = 0; i < pathLength-1; i++)
		{
			if (cf[path[i]][path[i + 1]] < cfp)
				cfp = cf[path[i]][path[i + 1]];
		}

		//aktualizuje przeplyw
		for (int i = 0; i < pathLength - 1; i++)
		{
			if (incidenceMatrix->edgeExists(path[i], path[i + 1]))
				f[path[i]][path[i + 1]] = f[path[i]][path[i + 1]] + cfp;
			else f[path[i]][path[i + 1]] = f[path[i]][path[i + 1]] - cfp;
		}


		//aktualizuje siec rezydualna
		for (int i = 0; i < nodeNumber; i++)
		{
			for (int j = 0; j < nodeNumber; j++)
			{
				if (incidenceMatrix->edgeExists(i, j))
				{
					cf[i][j] = c[i][j] - f[i][j];
					cf[j][i] = f[i][j];
				}
	
			}
		}
	}

	/*
	cout << "c:\n";
	for (int i = 0; i < nodeNumber; i++)
	{
		for (int j = 0; j < nodeNumber; j++)
		{
			cout << c[i][j] << " ";
		}
		cout << endl;
	}

	cout << "cf:\n";
	for (int i = 0; i < nodeNumber; i++)
	{
		for (int j = 0; j < nodeNumber; j++)
		{
			cout << cf[i][j] << " ";
		}
		cout << endl;
	}

	cout << "f:\n";
	for (int i = 0; i < nodeNumber; i++)
	{
		for (int j = 0; j < nodeNumber; j++)
		{
			cout << f[i][j] << " ";
		}
		cout << endl;
	}
	*/

	//W macierzy f pierwszy wiersz oznacza wyjœcie ze Ÿród³a, natomiast ostatnia kolumna wejœcie do ujœcia.
	//Maksymalny przep³yw to suma przep³ywów wychodz¹cych ze Ÿród³a (równa sumie wchodz¹cych do ujœcia)
	int sum1 = 0;
	int sum2 = 0;
	for (int i = 0; i < nodeNumber; i++)
	{
		sum1 += f[0][i];
		sum2 += f[i][nodeNumber - 1];
	}
	if (sum1 != sum2)
		cout << "Cos posz³o nie tak. Nie zostal zachowany warunek przeplywu.\n";
	else
		cout << "Maksymalny przeplyw wynosi: " << sum1 << endl;

}

int expPath(FlowNetwork* net, int* path)
{
	//BFS
	int* d = new int[net->nodeNumber];
	int* p = new int[net->nodeNumber];

	for (int i = 0; i < net->nodeNumber; i++)
	{
		d[i] = 1000;
		p[i] = -1;
	}

	d[0] = 0;
	std::queue<int> Q;
	Q.push(0);

	while (!Q.empty())
	{
		int v = Q.front();
		Q.pop();
		for (int u = 0; u < net->nodeNumber; u++)
		{
			if ((net->cf[v][u])>0)
			{
				if (d[u] == 1000)
				{
					d[u] = d[v] + 1;
					p[u] = v;
					Q.push(u);
				}
			}
		}

	}

	//ostatni index w tablicach p i d - numer ostatniego wierzcholka
	int lastIndex = net->nodeNumber - 1;

	//jesli nie udalo sie dotrzec do konca
	if (d[lastIndex] == 1000)
	{
		//sciezka nie zosta³a znaleziona
		return 0;
	}

	//ilosc wierzcholkow w scie¿ce rozszerzaj¹cej
	int pathNumberOfNodes = d[lastIndex] + 1;

	//sciezka ma po kolei wierzcholki wchodzace w jej sk³ad
	path[0] = 0;
	path[pathNumberOfNodes - 1] = lastIndex;
	for (int i = pathNumberOfNodes - 2; i > 0; i--)
	{
		path[i] = p[path[i + 1]];
	}

	return pathNumberOfNodes;
}