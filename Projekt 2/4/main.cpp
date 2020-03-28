#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
	int n;
	string vertices;
	
	cout << "Podaj ilość wierzchołków: ";
	cin >> n;

	vertices = eulerianVertices(n);

	Graph graph(vertices);

	if(graph.Check())
	{
		cout << "Podany ciag jest ciagiem graficznym." << endl;
		graph.BuildGraph();
		graph.DrawGraph("output1.dot");
		
		cout << "-------------------\n";
		cout << "Znaleziony cykl Eulera:\n";
		graph.findEulerianCircuit();
		cout << "\n-------------------\n";

	}
	else
	{
		cout << "Podany ciag nie jest ciagiem graficznym." << endl;
	}
    
	return 0;
}