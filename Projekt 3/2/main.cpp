#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
	int n;
	int start;
	
	cout << "Podaj ilosc wierzcholkow: ";
	cin >> n;
	
	if(n < 3)
	{
		cout << "Liczba wierzcholkow musi byc wieksze od 2!";
		return 0;
	}
	
	Graph graph(n);
	graph.DrawGraph("output.dot");
	
	cout << "Podaj wierzcholek startowy: ";
	cin >> start;
	if(start < 0 || start > n - 1)
	{
		cout << "Zle podany wierzcholek startowy!";
		return 0;
	}
	
	graph.Dijkstra(start);

	return 0;
}
