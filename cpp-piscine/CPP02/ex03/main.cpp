#include "Point.hpp"
#include <iostream>

bool	bsp(Point const a, Point const b, Point const c, Point p);

int	main() {
	Point	a(0, 0);
	Point	b(0, 1);
	Point	c(1, 0);

	std::cout << bsp(a, b, c, Point(0.1f, 0.1f)) << std::endl;
	std::cout << bsp(a, b, c, Point(1, 1)) << std::endl;
	std::cout << bsp(a, b, c, Point(0, 1)) << std::endl;
	std::cout << bsp(a, b, c, Point(0, 0)) << std::endl;
	std::cout << bsp(a, b, c, Point(1, 0)) << std::endl;
	std::cout << bsp(a, b, c, Point(1, 1.5f)) << std::endl;
	std::cout << bsp(a, b, c, Point(.2f, .2f)) << std::endl;
	std::cout << bsp(a, b, c, Point(.5f, .5f)) << std::endl;
	std::cout << bsp(a, b, c, Point(.49f, .49f)) << std::endl;


	std::cout << "-----------------------\n";

	Point	a2(1, 1);
	Point	b2(3, 3);
	Point	c2(2, 1.5);

	std::cout << bsp(a2, b2, c2, Point(1, 1)) << std::endl;
	std::cout << bsp(a2, b2, c2, Point(1.5, 1)) << std::endl;
	std::cout << bsp(a2, b2, c2, Point(0, 0)) << std::endl;
	std::cout << bsp(a2, b2, c2, Point(2, 1.7)) << std::endl;
}
