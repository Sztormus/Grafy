#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
	Graph graph("input.txt");
	string answer = graph.Hamilton();
	if(answer == "")
		cout << "Graf nie ma cyklu Hamiltona" << endl;
	else
		cout << answer << endl;
	return 0;
}
