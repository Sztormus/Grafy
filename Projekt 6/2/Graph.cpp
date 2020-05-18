#include "Graph.h"
#include <fstream>
#include <iostream>
#include <string>
#include <sstream> 
#include <algorithm>
#include <math.h>

using namespace std;

Graph::Graph(std::string input)
{
	cout << "Wczytywanie danych z pliku: " << input << endl;

	ifstream wej(input);
	string line, check;
	int n = 0;
	
	getline(wej, line);
	check = line;
	++n;
	getline(wej, line);
	while(line != check && line != "")
	{
		++n;
		check = line;
		getline(wej, line);
	}
	size = n;
	wej.close();

	x_coordinate = new int[size];
	y_coordinate = new int[size];
	
	ifstream wej2(input);
	getline(wej2, line);
	check = line;
	stringstream ss; 
	string temp;
	int found;
	int counter=0;
	for(int i = 0; i < size; ++i){
		ss.clear();
		ss << line;
		ss >> temp;
		while (!ss.eof()) {
        	stringstream(temp) >> found;
			counter++;
			if (counter%2==1)
				x_coordinate[i] = found;
			else
				y_coordinate[i]=found;

			ss >> temp;
    	} 
		check = line;
		getline(wej2, line);
	}
	stringstream(temp) >> found;
	y_coordinate[size-1]=found;

	adjacencyMatrix = new AdjacencyMatrix(size);
	for(int i = 0; i < size; ++i){
		for(int j = i + 1; j < size; ++j){
			adjacencyMatrix->setEdge(i, j, CalculateWage(i, j) );
		}
		
	}
}

double Graph::CalculateWage(int i, int j){
	int a, b;
	a = x_coordinate[i]>x_coordinate[j] ? abs(x_coordinate[i]-x_coordinate[j]) : abs(x_coordinate[i]-x_coordinate[j]);
	b = y_coordinate[i]>y_coordinate[j] ? abs(y_coordinate[i]-y_coordinate[j]) : abs(y_coordinate[i]-y_coordinate[j]);
	return sqrt(a*a+b*b);
}

void Graph::Hamilton()
{
	circuit = new int[size+1];
	for(int i = 0; i < size; ++i){
		circuit[i] = i;
	}
	circuit[size] = 0;
}

void Graph::MixHamilton(int a, int b, int c, int d){
	for(int i = 0; i < size+1; ++i){
		mixed_circuit[i] = circuit[i];
	}
	mixed_circuit[a] = c;
	mixed_circuit[b] = d;
	mixed_circuit[c] = a;
	mixed_circuit[d] = b;
}

double Graph::SumWages(int* name){
	double temp = 0.;
	for(int i = 1; i < size; ++i){
		temp += adjacencyMatrix->getEdge(name[i-1], name[i]);	
	}
	temp += adjacencyMatrix->getEdge(name[size-1], name[size]);	
	return temp;
}


double Graph::Annealing(){
	Hamilton();
	mixed_circuit = new int[size+1];
	double T;
	int a, b, c, d;
	double wages, mixed_wages;
	double r;
	wages = SumWages(circuit);

	for (int i=100; i>= 1; i--){
		srand( time( NULL ) );
		T = 0.001*i*i;
		for (int it=0; it<10000; it++){
			a = rand()%size;
			if(a!=199) b = a+1;
			else b=0;
			do{
				c = rand()%size;
			} while (c==a || c==b || c==(a-1));
			if(c!=199) d = c+1;
			else d=0;

			MixHamilton(a, b, c, d);

			mixed_wages = SumWages(mixed_circuit);
			if ( mixed_wages < wages ){
				wages = mixed_wages;
				for(int i = 0; i < size+1; ++i)
					circuit[i] = mixed_circuit[i];
			}
			else{
				r = rand()%100 / 100.;
				if ( r < exp( -(mixed_wages-wages)/T ) ){
					wages = mixed_wages;
					for(int i = 0; i < size+1; ++i)
						circuit[i] = mixed_circuit[i];
				}
			}
		}
		// cout << "Pętla zewnętrzna nr " << i << endl;
	}
	return wages;
}

void Graph::DrawGraph(std::string file){
	ofstream wyj(file);

	for(int i = 0; i < size+1; ++i){
		wyj << x_coordinate[circuit[i]] << "\t" << y_coordinate[circuit[i]] << endl;
	}
	
	cout << "Wygenerowano skrypt o nazwie '" << file << "' dla grafu o liczbie wierzcholkow: " << size << endl;
	
	wyj.close();
}


Graph::~Graph()
{
	delete adjacencyMatrix;
	delete[] x_coordinate;
	delete[] y_coordinate;
	delete[] circuit;
	delete[] mixed_circuit;
}


