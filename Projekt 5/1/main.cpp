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

	net.DrawNetwork("output.dot");

	return 0;
}
