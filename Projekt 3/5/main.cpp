#include <iostream>
#include "Graph.h"

using namespace std;
//algorytm prima

int main()
{
	int n;
	
	cout << "Podaj ilosc wierzcholkow: ";
	cin >> n;
	
	if(n < 3)
	{
		cout << "Liczba wierzcholkow musi byc wieksze od 2!";
		return 0;
	}
	
	Graph graph(n);
	graph.DrawGraph("output.dot");
	cout << "Minimalne drzewo rozpinające:" << endl;
	graph.Kruskal(n);
	graph.DrawGraph("tree.dot");


	return 0;
}
