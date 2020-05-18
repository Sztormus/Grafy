#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
	Graph graph("input.txt");
	double final = graph.Annealing();
	cout << "\nDługość cyklu: " << final << "\n\n";
	graph.DrawGraph("output.txt");
	return 0;
}
