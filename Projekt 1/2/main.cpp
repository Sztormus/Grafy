#include <iostream>
#include "DrawGraph.hpp"
#include <string>
#include <cstdlib>
#include <stdexcept>

using namespace std;

int main()
{
	string n, r, x, y;
	cout << "Podaj ilosc wierzcholkow: ";
	cin >> n;
	cout << "Podaj promien: ";
	cin >> r;
	cout << "Podaj wspolrzedna x srodka kola: ";
	cin >> x;
	cout << "Podaj wspolrzedna x srodka kola: ";
	cin >> y;
	
	try
	{
		if(stoi(n) < 1)
		{
			cerr << "Liczba wierzcholkow musi byc wieksza od zera!" << endl;
		}
		if(stod(r) <= 0)
		{
			cerr << "Promien musi byc wiekszy od zera!" << endl;
		}
		DrawGraph G(stoi(n), stod(r), stod(x), stod(y));
		G.GenerateScript();
	}
	catch (const std::invalid_argument& ia)
	{
		cerr << "Jeden lub wiecej wprowadzonych argumentow ma nieprawidlowa forme!" << endl;
	}
	return 0;
}
