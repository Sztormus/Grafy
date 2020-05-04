#include <iostream>
#include "Digraph.h"

using namespace std;

int main()
{
	int n;
	double p;
	int* comp;
	
	cout << "Podaj ilosc wierzcholkow: ";
	cin >> n;
	cout << "Podaj prawdopodobienstwo: ";
	cin >> p;
	
	if(n < 0 || p > 1 || p < 0)
	{
		cout << "Podales niewlasciwe dane!" << endl;
		return 0;
	}
	
	Digraph graph(n, p);
	
	comp = graph.Kosaraju();
	
	int k = 1;
	bool check;
	cout << "Silnie spojne skladowe:" << endl;
	while(true)
	{
		check = true;

		for(int i = 0; i < n; ++i)
		{
			if(comp[i] == k)
			{
				if(check)
					cout << k << ": ";
				cout << i << " ";
				check = false;
			}
		}
		cout << endl;

		++k;
		if(check)
			break;
	}

	k = max_num(comp, n);
	graph.selectConnectedGraph(comp, k);	

	int** D = graph.Johnson();
	if (D==nullptr){
		cout << "Algorytm Johnsona nie powiódł się, wystepuje cykl o ujemnych wagach." << endl;
	}
	else{
		cout << "-------------------\n";
		cout << "Macierz odleglosci: \n";
		for (int i = 0; i < graph.getSize(); i++)
		{
			for (int j = 0; j < graph.getSize(); j++)
			{
				if(D[i][j] >= 0 && D[i][j] < 10)
					cout << " " << D[i][j] << "  ";
				else if(D[i][j] > 9)
					cout << " " << D[i][j] << " ";
				else if (D[i][j] > -10 && D[i][j] < 0)
					cout << D[i][j] << "  ";
				else
					cout << D[i][j] << " ";
			}
			cout << endl;
		}
		cout << "-------------------\n";
	}

	delete[] comp;
	return 0;
}
