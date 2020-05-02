#include "Digraph.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <stack>

using namespace std;

Digraph::Digraph(int n, double p): size(n)
{
	srand(time(NULL));
	
	adjacencyMatrix = new AdjacencyMatrix(size);
	adjacencyList = new AdjacencyList(size);
	incidenceMatrix = new IncidenceMatrix(size);
	
	for(int i = 0; i < size; ++i)
	{
		for(int j = 0; j < size; ++j)
		{
			if((rand()/(double)RAND_MAX) < p)
			{
				adjacencyMatrix->setEdge(i, j);
				adjacencyList->setEdge(i, j);
				incidenceMatrix->setEdge(i, j);
			}
		}
	}
	
	for(int i = 0; i < size; ++i)
	{
		for(int j = 0; j < size; ++j)
		{
			if(incidenceMatrix->edgeExists(i, j))
				++edgeNumber;
		}
	}
	
	if(edgeNumber > 0)
	{
		wages = new int[edgeNumber][3];
	
		int k = 0;
		for(int i = 0; i < size; ++i)
		{
			for(int j = 0; j < size; ++j)
			{
				if(incidenceMatrix->edgeExists(i, j))
				{
					wages[k][0] = i;
					wages[k][1] = j;
					wages[k][2] = rand()%10 + 1;
					++k;
				}
			}
		}
	}
	
	adjacencyMatrix->print();
	adjacencyList->print();
	incidenceMatrix->print();
	
	/*if(edgeNumber > 0)
	{
		cout << "Wagi dla poszczegolnych krawedzi:" << endl;
		for(int i = 0; i < edgeNumber; ++i)
		{
			cout << wages[i][0] << "-" << wages[i][1] << ": " << wages[i][2] << endl;
		}
		cout << endl;
	}*/
}

int* Digraph::Kosaraju()
{
	AdjacencyMatrix Gt(size);
	int* f = new int[size];
	int* d = new int[size];
	int* comp = new int[size];
	int t = 0;
	int nr = 0;
	
	for(int v = 0; v < size; ++v)
	{
		f[v] = -1;
		d[v] = -1;
	}
	
	for(int v = 0; v < size; ++v)
	{
		if(d[v] == -1)
		{
			Visit(v, t, d, f);
		}
	}

	for(int i = 0; i < size; ++i)
	{
		for(int j = 0; j < size; ++j)
		{
			if(i == j)
				continue;
			if(adjacencyMatrix->edgeExists(i, j))
			{
				Gt.setEdge(j, i);
			}
		}
	}

	for(int v = 0; v < size; ++v)
		comp[v] = -1;
		
	bool* check = new bool[size];
	stack<int> S;
	int index;
	int value;
	
	for(int v = 0; v < size; ++v)
		check[v] = false;
		
	while(S.size() < size)
	{
		index = -1;
		value = INT_MAX;
		
		for(int i = 0; i < size; ++i)
		{
			if(f[i] < value && check[i] == false)
			{
				value = f[i];
				index = i;
			}
		}
		
		check[index] = true;
		S.push(index);
	}
	
	while(!S.empty())
	{
		int v = S.top();
		S.pop();
		
		if(comp[v] == -1)
		{
			++nr;
			comp[v] = nr;
			Components(nr, v, comp, Gt);
		}
	}
	
	delete[] d;
	delete[] f;
	delete[] check;
	
	return comp;
}

void Digraph::Visit(int v, int& t, int* d, int* f)
{
	++t;
	d[v] = t;
			
	for(int u = 0; u < size; ++u)
	{
		if(u != v && adjacencyMatrix->edgeExists(v, u))
		{
			if(d[u] == -1)
				Visit(u, t, d, f);
		}
	}
	
	++t;
	f[v] = t;
}

void Digraph::Components(int& nr, int v, int* comp, AdjacencyMatrix& Gt)
{
	for(int u = 0; u < size; ++u)
	{
		if(u != v && Gt.edgeExists(v, u))
		{
			if(comp[u] == -1)
			{
				comp[u] = nr;
				Components(nr, u, comp, Gt);
			}
		}
	}
}


void Digraph::SSS(int* comp, int k){
	int tab[size];
	int it = 0;
	for(int i = 0; i<size; i++){
		if (comp[i] == k) {
			tab[it] = i;
			cout<< tab[it]<<" ";
			it++;
		}
	}
	cout<<endl;

	for(int i = 0; i<size; i++){
		for(int j = 0; j<size; j++){
			if(in_tab(i,tab) && in_tab(j, tab)){
				setWage(i, j);
			}
			else{
				//usun krawedz jesli istnieje
				incidenceMatrix->deleteEdge(i, j);
			}
		}
	}
	incidenceMatrix->print();
}
int max_num(int *comp, int n){
	int max [2];
	max[0] = 1;	//k
	max[1] = 0;	//wierzcholki
	int k = 1;
	int temp;
	bool check;
	while(true) {
		check = true;
		temp = 0;
		for(int i = 0; i < n; ++i) {
			if(comp[i] == k)
			{
				temp++;
				check = false;
			}
		}
		if(temp>max[1]) {
			max[0] = k;
			max[1] = temp;
			}
		++k;

		if(check)
			break;
	}
	return max[0];

}

bool Digraph::Bellman_Ford(int w, int s){

	//INIT(G,s), s - wierzcholek zrodlo
	int* ds = new int[size];
	int* ps = new int[size];
	for(int i = 0; i < size; ++i) {
		ds[i] = INT_MAX;
		ps[i] = -1;
	}
	ds[s] = 0;

	for(int i = 0; i < size; ++i) {
		for(int j = 0; j < size; ++j) {
			if(incidenceMatrix->edgeExists(i, j)){
				//RElAX
				if (ds[j] > ds[i] + getWage(i, j)) {
					ds[j] = ds[i] + getWage(i, j);
					ps[j] = i;
				}
			}
		}
	}
	for(int i = 0; i < size; ++i) {
		for(int j = 0; j < size; ++j) {
			if(incidenceMatrix->edgeExists(i, j)){
				if(ds[i] > ds[j] + getWage(i, j)) return false;
			}
		}
	}
	return true;
}

void Digraph::setWage(int a, int b){
	for(int i = 0; i < edgeNumber; ++i){
		if(wages[i][0] == a && wages[i][1] == b) {
			wages[i][2] = rand()%15-5;
			cout<<a<<"-"<<b<<": "<<wages[i][2]<<endl;
			break;
		}
	}
}
int Digraph::getWage(int a, int b){
	for(int i = 0; i < edgeNumber; ++i){
		if(wages[i][0] == a && wages[i][1] == b) {
			return wages[i][2];
		}
	}
	return 0;
}

bool Digraph::in_tab(int number, int* tab){
	for(int i =0; i< size; i++){
		if(tab[i] == number) return true;
	}
	return false;
}

Digraph::~Digraph()
{
	delete adjacencyList;
	delete adjacencyMatrix;
	delete incidenceMatrix;
	delete[] wages;
}
