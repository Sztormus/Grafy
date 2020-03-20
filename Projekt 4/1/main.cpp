#include <iostream>
#include "Digraph.h"

using namespace std;

int main()
{
	int n;
	double p;
	
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
	return 0;
}
