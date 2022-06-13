#include "Fixed.hpp"
#include <iostream>

Fixed::Fixed() {
	std::cout << "Default constructor called" << std::endl;
	this->raw = 0;
}

Fixed::Fixed(const Fixed& f) {
	std::cout << "Copy constructor called" << std::endl;
	// this->raw = f.raw;
	this->raw = f.getRawBits();
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

Fixed& Fixed::operator=(const Fixed& f) {
	std::cout << "Assignation operator called" << std::endl;
	/* if (this == &f)
		return *this; */
	// this->raw = f.raw;
	this->raw = f.getRawBits();
	return *this;
}
