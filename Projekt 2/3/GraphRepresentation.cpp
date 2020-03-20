#include "pch.h"
#include <iostream>
#include "GraphRepresentation.h"

using namespace std;

int GraphRepresentation::basicCheck(int node1, int node2)
{
	if (node1 < 0 || node1 >= nodes || node2 < 0 || node2 >= nodes)
	{
		cout << "Nie ma takiego wezla. Nie dodano jednej z krawedzi.\n";
		return 0;
	}
	if (node1 == node2)
	{
		cout << "Graf prosty nie moze laczyc wezla z samym soba.\n";
		return 0;
	}
	if (edgeExists(node1, node2))
	{
		cout << "Krawedz juz istnieje\n";
		return 0;
	}
	return 1;
}