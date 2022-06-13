#ifndef POINT_H
# define POINT_H

# include "Fixed.hpp"

class Point {
public:
	Point();
	Point(const Point&);
	Point(float const, float const);
	~Point();

	const Fixed&	getx() const;
	const Fixed&	gety() const;

	Point&	operator =(const Point&);

private:
	Fixed const	x;
	Fixed const	y;
};

#endif
