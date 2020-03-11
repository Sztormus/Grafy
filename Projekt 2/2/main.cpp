#include <iostream>
#include "Graph.h"

using namespace std;

int main()
{
	int randomization;
	string input;
	
	cout << "Podaj ciag: ";
	getline(cin, input);
	cout << "Podaj ilosc randomizacji: ";
	cin >> randomization;
	
	Graph graph(input);
	if(graph.Check())
	{
		cout << "Podany ciag jest ciagiem graficznym." << endl;
		graph.BuildGraph();
		graph.DrawGraph("output1.dot");
		
		cout << "Podana liczba randomizacji grafu: " << randomization << endl;
		graph.Shuffle(randomization);
		graph.DrawGraph("output2.dot");
	}
	else
	{
		cout << "Podany ciag nie jest ciagiem graficznym." << endl;
	}
	return 0;
}
