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
	
	delete[] comp;
	return 0;
}
