#include "pch.h"
#include <iostream>
#include "FlowNetwork.h"

using namespace std;

int main()
{
	int N;
	
	cout << "Podaj ilosc warstw: ";
	cin >> N;
	
	if(N < 2)
	{
		cout << "Podales niewlasciwe dane!" << endl;
		return 0;
	}
	
	FlowNetwork net(N);

	

	net.FordFulkerson();
	net.DrawNetwork("capacity.txt");
	net.DrawFlow("flow.txt");

	return 0;
}

