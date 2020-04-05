#include <iostream>
#include "Digraph.h"

using namespace std;

int main()
{
	Digraph graph("input.txt");
	graph.PageRank();
	return 0;
}
