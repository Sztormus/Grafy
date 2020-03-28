#include "pch.h"
#include <iostream>
#include "GraphRepresentation.h"

using namespace std;

int GraphRepresentation::basicCheck(int node1, int node2)
{
	if (node1 < 0 || node1 >= nodes || node2 < 0 || node2 >= nodes)
	{
		return 0;
	}
	if (node1 == node2)
	{
		return 0;
	}
	if (edgeExists(node1, node2))
	{
		return 0;
	}
	return 1;
}
