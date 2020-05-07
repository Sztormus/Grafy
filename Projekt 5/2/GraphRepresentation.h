#pragma once

//Abstrakcyjna klasa bedaca interfejsem dla roznych reprezentacji grafu.
class GraphRepresentation
{
public:
	virtual ~GraphRepresentation() {} 

	//Metoda sluzaca wypisaniu reprezentacji grafu w formie liczbowej (macierze, lista)
	virtual void print() = 0;
	
	//Metoda dodajaca polaczenie pomiedzy wezlami node1 i node2
	virtual void setEdge(int node1, int node2) = 0;

	//Metoda sprawdzajaca warunek czy krawedz o zadanych koncach juz istnieje
	virtual int edgeExists(int node1, int node2) = 0;

	//Metoda sprawdzajaca, czy podane wezly moga stworzyc krawedz grafu (z uwzglednieniem warunkow zadanych na graf prosty)
	// Zwraca 1, jesli wezly przeszly test i mozna stworzyc takie polaczenie
	int basicCheck(int node1, int node2);

protected:
	//iosc wezlow (okreslana przy konstruowaniu grafu)
	int nodes;
	//ilosc krawedzi (aktualizowana po kazdym dodaniu krawedzi)
	int edges;
	//reprezentacja macierzy badz listy (oba w formie tablicy dwuwymiarowej)
	int**Representation;

};
