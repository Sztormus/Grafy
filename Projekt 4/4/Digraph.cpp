#include "Digraph.h"
#include <iostream>
#include <cstdio>
#include <cstdlib>
#include <ctime>
#include <stack>
#include <set>
#include <limits.h>

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
					wages[k][2] = 0;
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
		value = INT_MAX/2;
		
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

//////////////////////////////////////////////////////////
void Digraph::selectConnectedGraph(int* comp, int k){
	int tab[size]{-1};
	int it = 0;
	cout << "Wybrano składową zawierającą wierzchołki: " ;
	for(int i = 0; i<size; i++){
		if (comp[i] == k) {
			tab[it] = i;
			cout<< tab[it]<<" ";
			it++;
		}
	}
	cout<<endl;

	if (it==1){
		cout << "Nie znaleziono silnie spójnej składowej, która miałaby co najmniej 2 wierzchołki.\n" ;
		exit(-1);
	}

	for(int i = 0; i<size; i++){
		for(int j = 0; j<size; j++){
			if ( incidenceMatrix->edgeExists(i, j) ){
				if(in_tab(i,tab) && in_tab(j, tab)){
				}
				else{
					incidenceMatrix->deleteEdge(i, j);
				}
			}
		}
	}

	if ( it < size ){
		int** matrix = new int*[size];
		for (int i=0; i<(size); i++)
			matrix[i] = new int[edgeNumber];

		for (int i=0; i<size; i++){
			for (int j=0; j<edgeNumber; j++)
				matrix[i][j] = incidenceMatrix->getRepresentation(i, j);
		}
		delete incidenceMatrix;
		incidenceMatrix = new IncidenceMatrix(it);
		
		int counter=0;
		newNodes = new int[size]{-1};
		for(int i = 0; i<size; i++){
				if (comp[i] == k) {
					newNodes[i] = counter;
					counter++;
				}
				else{
					newNodes[i] = -1;
				}
		}
		edgeNumber0 = 0;
		for(int i = 0; i<size; i++){
			for(int j = 0; j<size; j++){
				if ( edgeExists(matrix, i, j) ){
					incidenceMatrix->setEdge(newNodes[i], newNodes[j]);
					edgeNumber0++;
				}
			}
		}
		size=it;
		edgeNumber = edgeNumber0;
		incidenceMatrix->print();
	}
	else
		cout << "Macierz incydencji pozostaje bez zmian" << endl;
	
	cout << "Ilosc krawedzi w spójnej składowej: " << edgeNumber << endl << "Ilość wierzchołków w spójnej składowej: " << size << endl;
	cout << "-------------------\n";

	delete[] wages;
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
					wages[k][2] = rand()%15-5;
					++k;
				}
			}
		}
	}
	if(edgeNumber > 0)
	{
		cout << "Wagi dla poszczegolnych krawedzi:" << endl;
		for(int i = 0; i < (edgeNumber); ++i)
		{
			cout << wages[i][0] << "-" << wages[i][1] << ": " << wages[i][2] << endl;
		}
	}
	cout << "-------------------\n";
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

bool Digraph::Bellman_Ford(int** G_prim, int (*wages)[3], int s){

	//INIT(G,s), s - wierzcholek zrodlo
	ds = new int[size];
	ps = new int[size];
	for(int i = 0; i < size; ++i) {
		ds[i] = INT_MAX/2;
		ps[i] = -1;
	}
	ds[s] = 0;

	for(int l = 1; l<size; l++){
		for(int i = 0; i < size; ++i) {
			for(int j = 0; j < size; ++j) {
				if( edgeExists(G_prim, i, j) ){
					//RElAX
					if (ds[j] > ds[i] + getWage(i, j)) {
						ds[j] = ds[i] + getWage(i, j);
						ps[j] = i;
					}
				}
			}
		}
	}
	for(int i = 0; i < size; ++i) {
		for(int j = 0; j < size; ++j) {
			if( edgeExists(G_prim, i, j) ){
				if(ds[j] > ds[i] + getWage(i, j)) return false;
			}
		}
	}
	return true;
}

void Digraph::setWage(int a, int b, int value){
	for(int i = 0; i < edgeNumber; ++i){
		if(wages[i][0] == a && wages[i][1] == b) {
			wages[i][2] = value;
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

bool Digraph::edgeExists(int** G_prim, int node1, int node2){
	for (int i = 0; i < edgeNumber ; i++){
		if (G_prim[node1][i] == 1 && G_prim[node2][i] == -1) return true;
	}
	return false;
}

bool Digraph::in_tab(int number,  int* tab){
	for(int i=0; i<size; i++){
		if(tab[i] == number) return true;
	}
	return false;
}

////////////////////////////////////////////////////////// 
int** Digraph::add_s(){
	int** G_prim = new int*[size+1];
	for (int i=0; i<(size+1); i++)
		G_prim[i] = new int[edgeNumber+size];

	for (int i=0; i<size; i++){
		for (int j=0; j<edgeNumber; j++)
			G_prim[i][j] = incidenceMatrix->getRepresentation(i, j);
		for (int j=edgeNumber; j<(edgeNumber+size); j++){
			if ( (j-edgeNumber) == i )
				G_prim[i][j] = -1;
			else
				G_prim[i][j] = 0;
		}	
	}
	for (int j=0; j<(edgeNumber+size); j++){
		if (j<edgeNumber)
			G_prim[size][j] = 0;
		else
			G_prim[size][j] = 1;
		
	}

	return G_prim;
}

int* Digraph::Dijkstra(int start){
	int* d = new int[size];
	int* p = new int[size];
	set<int> S;

	for (int i = 0; i < size; ++i){
		d[i] = INT_MAX/2;
		p[i] = -1;
	}
	d[start] = 0;

	int u = -1;
	int dist = INT_MAX/2;
	while (S.size() < size){
		u = -1;
		dist = INT_MAX/2;
		for (int i = 0; i < size; ++i){
			if (d[i] < dist && S.count(i) == 0){
				dist = d[i];
				u = i;
			}
		}
		S.insert(u);

		for (int v = 0; v < size; ++v){
			if (v == u)
				continue;
			if (S.count(v) == 0 && incidenceMatrix->edgeExists(u, v)){
				int k = 0;
				while (true){
					if (wages[k][0] == u && wages[k][1] == v){
						break;
					}
					else
						++k;
				}

				if (d[v] > d[u] + wages[k][2]){
					d[v] = d[u] + wages[k][2];
					p[v] = u;
				}
			}
		}
	}
	delete[] p;
	return d;
}

int** Digraph::Johnson(){
	int** G_prim = add_s();
	int edgeNumber_prim = edgeNumber + size;
	int (*wages_prim)[3] = new int[edgeNumber_prim][3];
	for (int k=0; k<edgeNumber; k++){
		wages_prim[k][0] = wages[k][0];
		wages_prim[k][1] = wages[k][1];
		wages_prim[k][2] = wages[k][2];
	}
	delete[] wages;
	wages = new int[edgeNumber_prim][3];
	for (int k=0; k<edgeNumber; k++){
		wages[k][0] = wages_prim[k][0];
		wages[k][1] = wages_prim[k][1];
		wages[k][2] = wages_prim[k][2];
	}
	delete[] wages_prim;
	for (int k=edgeNumber; k<edgeNumber_prim; k++){
		wages[k][0] = size;
		wages[k][1] = k-edgeNumber;
		wages[k][2] = 0;
	}

	// cout << "G_prim" << endl;
	// for (int i=0; i<(size+1); i++){
	// 	for (int j=0; j<(edgeNumber_prim); j++){
	// 		if(G_prim[i][j] == 1 || G_prim[i][j] == 0)
	// 			cout << " " << G_prim[i][j] << " ";
	// 		else
	// 			cout << G_prim[i][j] << " ";
	// 	}
	// 	cout << endl;
	// }
	// cout << "-------------------\n";
	// if(edgeNumber_prim > 0){
	// 	cout << "Wagi dla poszczegolnych krawedzi:" << endl;
	// 	for(int i = 0; i < (edgeNumber_prim); ++i)
	// 	{
	// 		cout << wages[i][0] << "-" << wages[i][1] << ": " << wages[i][2] << "    ";
	// 	}
	// }
	// cout << "\n-------------------\n";

	edgeNumber+=size;
	size++;

	if ( !Bellman_Ford(G_prim, wages, size-1) ){
		int**D = nullptr;
		return D;
		
	}
	else{
		int* h = new int[size];
		for (int k=0; k<size; k++){
			h[k] = ds[k];
			// cout << h[k] << " " ;
		}

		for(int i = 0; i < size; ++i) {
			for(int j = 0; j < size; ++j) {
				if( edgeExists(G_prim, i, j) ){
					int temp = getWage(i, j) + h[i] - h[j];
					setWage(i, j, temp);
				}
			}
		}
		size--;
		edgeNumber-=size;
		int** D = new int*[size];
		for (int i=0; i<(size); i++)
			D[i] = new int[size];
		int** d = new int*[size];
		for (int i=0; i<size; i++){
			d[i] = Dijkstra(i);
			for (int j=0; j<size; j++){
				D[i][j] = d[i][j] - h[i] + h[j];
				// cout << D[i][j] << " " << d[i][j] << " " << h[i] << " " << h[j] << endl;
			}
		}
		return D;
	}
}

Digraph::~Digraph()
{
	delete adjacencyList;
	delete adjacencyMatrix;
	delete incidenceMatrix;
	delete[] wages;
	delete ds;
	delete ps;
	delete newNodes;
}
