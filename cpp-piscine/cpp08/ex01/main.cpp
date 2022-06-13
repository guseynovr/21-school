#include <Span.hpp>
#include <iostream>
#include <cstdlib>
#include <list>
#include <vector>
#include <algorithm>

int	genRand() {
	return std::rand() % 1000000;
}

int	gen() {
	static int	i;

	return i++;
}

int	main() {
	Span sp = Span(5);

	sp.addNumber(5);
	sp.addNumber(3);
	sp.addNumber(17);
	sp.addNumber(9);
	sp.addNumber(11);

	std::cout << sp.shortestSpan() << std::endl;
	std::cout << sp.longestSpan() << std::endl;

	std::vector<int> bigv(15000);
	std::generate(bigv.begin(), bigv.end(), gen);

	Span bigsp(15000);
	bigsp.addNumber(bigv.begin(), bigv.end());

	std::cout << bigsp.shortestSpan() << std::endl;
	std::cout << bigsp.longestSpan() << std::endl;

	try {
		bigsp.addNumber(1);
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::srand(std::time(0));
	std::vector<int> bigbigv(150000);
	std::generate(bigbigv.begin(), bigbigv.end(), genRand);

	Span bigbigsp(150000);
	bigbigsp.addNumber(bigbigv.begin(), bigbigv.end());

	std::cout << bigbigsp.shortestSpan() << std::endl;
	std::cout << bigbigsp.longestSpan() << std::endl;

	try {
		bigbigsp.addNumber(1);
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	std::list<int> bigbiglist(150000);
	std::generate(bigbiglist.begin(), bigbiglist.end(), genRand);

	Span bigbigsp2(150000);
	bigbigsp2.addNumber(bigbiglist.begin(), bigbiglist.end());

	std::cout << bigbigsp2.shortestSpan() << std::endl;
	std::cout << bigbigsp2.longestSpan() << std::endl;

	try {
		bigbigsp2.addNumber(1);
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
}
