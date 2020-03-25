#include <iostream>
#include "Graph.h"

using namespace std;

int main() {
    int n, k;
    cout<<"Podaj ilość wierzchołkow: ";
    cin>>n;
    cout<<"Podaj stopień: ";
    cin>>k;
    while(k<0 || k>=n) {
        cout <<"Niepoprawny stopień!"<<endl<<"Podaj stopień ponownie: ";
        cin>>k;
    }
    string input = "";
    for(int i = 0; i<n; i++){
        input += to_string(k) + " ";
    }
    cout<<"Ciag dla "<<n<<" wierzcholkow o stopniu "<<k<<": "<<input<<endl;

    Graph graph(input);
    if(graph.Check()){
		cout << "Podany ciag jest ciagiem graficznym." << endl;
		graph.BuildGraph();
		graph.DrawGraph("output1.dot");
		
		cout << "Losowy graf k-regularny: "<< endl;
		if(k!=0 && k!=n-1) graph.Shuffle(rand()%10);
		graph.DrawGraph("output2.dot");

        cout<<"Wynik znajduje sie w pliku output2.dot"<<endl;
	}
	else {
		cout << "Podany ciag nie jest ciagiem graficznym." << endl;
    }

	return 0;
}