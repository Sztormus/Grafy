#include <iostream>
#include <cstdlib>
#include "Graph.h"


Graph::Graph(const unsigned int nodes, const unsigned int lines, const float probability) : n(nodes), l(lines), p(probability)
{
    arr = new int*[n];
    for(unsigned int i = 0; i < n; ++i)
        arr[i] = new int[l-1];


    for(unsigned int i = 0; i < n; ++i)
    {
        for (unsigned int j = 0; j < l-1; ++j)
            arr[i][j] = 0;
    }
}


Graph::~Graph()
{
    for(unsigned int i = 0; i < n; ++i)
        delete [] arr[i];
    delete [] arr;
}



void Graph::generate()
{
    unsigned int x, y;
    unsigned int k = 0, j_x = 0, j_y = 0;
    bool exist = false;

    while ( k < l )
    {   
        x = std::rand() % n;
        y = std::rand() % n;

        if ( x!=y )
        {    
            exist = searchRow(arr[x], l-1, y+1);
            if (!exist)
            {
                while ( (arr[x][j_x] != 0)  && (j_x < (l-1)) )
                    j_x++;
                arr[x][j_x] = y+1;

                while ( (arr[y][j_y] != 0)  && (j_y < (l-1)) )
                    j_y++;
                arr[y][j_y] = x+1;
                
                j_x = 0;
                j_y = 0;
                k++;
            }
        }
    
        exist = false;
    }
}


void Graph::generateWithProbability()
{
    unsigned int k = 0, j_x = 0, j_y = 0;

    for (unsigned int x = 0; x < n; x++)
    {
        for (unsigned int y = (x+1); y < n; y++)
        {
            k = 1 + std::rand() % 100;
            
            if ( k <= p*100 )
            {
                while ( (arr[x][j_x] != 0)  && (j_x < (l-1)) )
                    j_x++;
                arr[x][j_x] = y+1;

                while ( (arr[y][j_y] != 0)  && (j_y < (l-1)) )
                    j_y++;
                arr[y][j_y] = x+1;
                
                j_x = 0;
                j_y = 0; 
            }

        }
    }
}

void Graph::printGraph()
{
    std::cout << "\nWygenerowany graf: " << std::endl;
    for(unsigned int i = 0; i < n; i++)
    {
        std::cout << "Węzeł " << i+1 << ":  " ;
        for(unsigned int j = 0; j < l-1; j++)
        {
            if( arr[i][j] != 0 )
                std::cout << arr[i][j] << " " ;
        }
        std::cout << std::endl;
    }
}


bool searchRow(int arr[], int length, int value)
{
	int i = 0;
	bool found = false;
	
	while ( (i < length) && (!found) )
	{
    	if (arr[i] == value)
        {
		    found = true;
            break;
        }
        i++;
    }
	
	return found;
}