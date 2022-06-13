#include "Fixed.hpp"
#include <cmath>

Fixed::Fixed() : raw(0) {
	std::cout << "Default constructor called" << std::endl;
}

Fixed::Fixed(const Fixed& f) : raw(f.raw) {
	std::cout << "Copy constructor called" << std::endl;
}

Fixed::Fixed(const int dec) : raw(dec << fbits) {
	std::cout << "Int constructor called" << std::endl;
}

Fixed::Fixed(const float fl)
	: raw(static_cast<int>(std::roundf(fl * (1 << Fixed::fbits)))) {
	std::cout << "Float constructor called" << std::endl;
}

Fixed::~Fixed() {
	std::cout << "Destructor called" << std::endl;
}

int		Fixed::getRawBits(void) const {
	std::cout << "getRawBits member function called" << std::endl;
	return this->raw;
}

void	Fixed::setRawBits(int const raw) {
	std::cout <<"setRawBits member function called" << std::endl;
	this->raw = raw;
}

float	Fixed::toFloat(void) const {
	return static_cast<float>(this->raw) / (1 << fbits);
}

int		Fixed::toInt(void) const {
	return this->raw >> Fixed::fbits;
}

Fixed& Fixed::operator=(const Fixed& f) {
	std::cout << "Assignation operator called" << std::endl;
	this->raw = f.raw;
	return *this;
}

std::ostream&	operator<<(std::ostream& os, const Fixed& f) {
	os << f.toFloat();
	return os;
}
