#include "Point.hpp"

Fixed sign(Point p1, Point p2, Point p3)
{
    return (p1.getx() - p3.getx()) * (p2.gety() - p3.gety())
		- (p2.getx() - p3.getx()) * (p1.gety() - p3.gety());
}

bool bsp(Point const a, Point const b, Point c, Point const p)
{
    Fixed	d1, d2, d3;
    bool	allNeg, allPos;

    d1 = sign(p, a, b);
    d2 = sign(p, b, c);
    d3 = sign(p, c, a);

    allNeg = d1 < 0 && d2 < 0 && d3 < 0;
    allPos = d1 > 0 && d2 > 0 && d3 > 0;

	// std::cout << "allNeg: " << allNeg << std::endl;
	// std::cout << "allPos: " << allPos << std::endl;
	// std::cout << "d1: " << d1 << std::endl;
	// std::cout << "d2: " << d2 << std::endl;
	// std::cout << "d3: " << d3 << std::endl;
    return (allNeg || allPos);
}
