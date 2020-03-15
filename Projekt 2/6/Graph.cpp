#include "Graph.h"
#include <fstream>
#include <iostream>
#include <string>

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
	wej.open("input.txt");
	getline(wej, line);
	check = line;
	
	adjacencyMatrix = new AdjacencyMatrix(size);
	for(int i = 0; i < size; ++i)
	{
		for(int j = i + 1; j < size; ++j)
		{
			if(line[2 * j] == '1')
			adjacencyMatrix->setEdge(i, j);
		}
		getline(wej, line);
	}
	adjacencyMatrix->print();
}

void Graph::GoInside(int first, int current, bool* visited, int* stack, int size)
{
	for(int i = 0; i < size; ++i)
	{
		
		if(stack[i] == -1)
		{
			stack[i] = current;
			break;
		}
	}
	
	visited[current] = 1;
	
	for(int i = 0; i < size; ++i)
		cout << stack[i] << " ";
	cout << endl;
	
	for(int i = 0; i < size; ++i)
		cout << visited[i] << " ";
	cout << endl << endl;
	
	for(int i = 0; i < size; ++i)
	{
		if(i == current)
			continue;
		
		if(adjacencyMatrix->edgeExists(i, current) && visited[i] == false)
		{
			bool check = true;
			
			GoInside(first, i, visited, stack, size);
			
			if(stack[size - 1] != -1)
			{
				if(adjacencyMatrix->edgeExists(first, stack[size - 1]))
				{
					return;
				}
				else
				{
					visited[stack[size - 1]] = 0;
					stack[size - 1] = -1;
					break;
				}
			}
			else
			{
				for(int i = 0; i < size; ++i)
				{
					if(stack[i] == -1)
					{
						visited[stack[i - 1]] = 0;
						stack[i - 1] = -1;
						break;
					}
				}
			}
		}
	}
}

string Graph::Hamilton()
{
	bool visited[size];
	int stack[size];
	string answer = "";
	
	for(int i = 0; i < size; ++i)
	{
		cout << "Wierzcholek poczatkowy: " << i << endl;
		bool check = true;
		
		for(int j = 0; j < size; ++j)
		{
			visited[j] = 0;
			stack[j] = -1;
		}
		
		GoInside(i, i, visited, stack, size);
		cout << endl << endl;
		
		if(stack[size - 1] != -1)
		{
			answer += "[";
			for(int j = 0; j < size; ++j)
			{
				answer += to_string(stack[j]);
				answer += " - ";
			}
			answer += to_string(i);
			answer += "]";
			
			return answer;
		}
	}
	
	return "";
}

Graph::~Graph()
{
	delete adjacencyMatrix;
}


