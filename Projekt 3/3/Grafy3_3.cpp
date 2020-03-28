#include "pch.h"
#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
	int n;

	cout << "Podaj ilosc wierzcholkow: ";
	cin >> n;

	if (n < 3)
	{
		cout << "Liczba wierzcholkow musi byc wieksze od 2!";
		return 0;
	}

	Graph graph(n);
	graph.DrawGraph("output.dot");
	graph.setDistanceMatrix();

	return 0;
}