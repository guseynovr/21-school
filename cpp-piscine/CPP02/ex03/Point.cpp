#include "Point.hpp"

Point::Point() : x(0), y(0) {}

Point::Point(const Point& p) : x(p.x), y(p.y) {}

Point::Point(float const x, float const y) : x(x), y(y) {}

Point::~Point() {}

const Fixed&	Point::getx() const {
	return x;
}

const Fixed&	Point::gety() const {
	return y;
}

Point&	Point::operator =(const Point& other) {
	static_cast<Fixed>(this->x) = other.x;
	static_cast<Fixed>(this->y) = other.y;

	return *this;
}
