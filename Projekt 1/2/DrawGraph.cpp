#define _USE_MATH_DEFINES
#include <iostream>
#include <fstream>
#include "DrawGraph.hpp"
#include <cmath>

#define EPS 1e-7

using namespace std;

DrawGraph::DrawGraph(const unsigned int n, const double r, const double x, const double y): node_number(n), r0(r), x0(x), y0(y)
{}

void DrawGraph::GenerateScript()
{
	ofstream wyj("graph.dot");
	double alpha = (2 * M_PI)/node_number;
	double position[node_number][2];
	
	for(int i = 0; i < node_number; ++i)
	{
		position[i][0] = x0 + r0 * cos(i * alpha);
		position[i][1] = y0 + r0 * sin(i * alpha);
		if(fabs(position[i][0]) < EPS)
			position[i][0] = 0;
		if(fabs(position[i][1]) < EPS)
		position[i][1] = 0;
	}
	
	wyj << "digraph G" << endl << "{" << endl;
	wyj << "	layout=\"circo\";" << endl;
	wyj << "	node [shape = circle];" << endl;
	for(int i = 1; i < node_number; ++i)
	{
		wyj << "	N" << node_number - i << " -> N" << node_number - i - 1 << " [arrowhead=none]" << endl;
	}
	wyj << "	N0 -> N" << node_number - 1 << " [arrowhead=none]" << endl << "}";
	wyj.close();
	
	cout << "Wygenerowano skrypt o nazwie 'graph.dot' dla grafu o liczbie wierzcholkow: " << node_number << endl;
	cout << "Wspolrzedne wierzcholkow:" << endl;
	for(int i = 0; i < node_number; ++i)
	{
		cout << "N" << i << " -> x: " << position[i][0] << ", y: " << position[i][1] << endl;
	}
}
