//Krótka biblioteka do obslugi roznych reprezentacji grafow.
//

#include "pch.h"
#include <iostream>
#include "AdjacencyList.h"
#include "AdjacencyMatrix.h"
#include "IncidenceMatrix.h"

using namespace std;

int main()
{
	AdjacencyMatrix* g = new AdjacencyMatrix(5);
	IncidenceMatrix* i = new IncidenceMatrix(5);
	AdjacencyList* h = new AdjacencyList(5);
	g->setEdge(2, 3);
	g->setEdge(4, 1);
	g->setEdge(0, 3);
	i->setEdge(2, 3);
	i->setEdge(2, 4);
	i->setEdge(2, 1);
	i->setEdge(0, 2);
	h->setEdge(2, 3);
	h->setEdge(1, 3);
	h->setEdge(0, 4);
	h->setEdge(4, 2);

	g->print();
	i->print();
	h->print();

	return 0;
}