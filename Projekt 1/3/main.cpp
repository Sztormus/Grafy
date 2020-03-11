#include <iostream>
#include <string>
#include <cstdlib>
#include <stdexcept>

#include "Graph.h"


int main()
{
    int n, l, a;
	float p;

	std::cout << "Jeśli chcesz podać liczbę połączeń mięczy wierzchołkami - wciśnij \"1\", jeśli chcesz podać prawdopodobieństwo występowania połączenia - wciśnij \"2\": ";
	std::cin >> a;

	if (a==1)
	{
		std::cout << "Podaj ilosc wierzcholkow: ";
		std::cin >> n;
		std::cout << "Podaj ilość połączeń: ";
		std::cin >> l;

		if( n < 1 )
		{
			std::cout << "Liczba wierzcholkow musi byc wieksza od zera!" << std::endl;
			return 0;
		}
		if( l <= 0 || l >= 0.5*n*(n-1) )
		{
			std::cout << "Liczba połączeń musi być niemniejsza od zera i niewiększa niż 0.5*n*(n-1)!" << std::endl;
			return 0;
		}

    	Graph G(n, l);
        G.generate();
	    G.printGraph();

		return 0;
	}

	else if (a==2)
	{
		std::cout << "Podaj ilosc wierzcholkow: ";
		std::cin >> n;
		std::cout << "Podaj prawdopodobieństo dla występowania połączenia: ";
		std::cin >> p;

		if( n < 1 )
		{
			std::cout << "Liczba wierzcholkow musi byc wieksza od zera!" << std::endl;
			return 0;
		}
		if( p < 0 || p > 1 )
		{
			std::cout << "Liczba prawdopodobieństwa musi być w przedziale od 0 do 1!" << std::endl;
			return 0;
		}
			
		l = 0.5*n*(n-1);
    	Graph G(n, l, p);
        G.generateWithProbability();
	    G.printGraph();

		return 0;
	}

	else
	{
		std::cout << "\nWprowadzono nieprawidłowy znak" << std::endl;
		return 0;
	}


}
