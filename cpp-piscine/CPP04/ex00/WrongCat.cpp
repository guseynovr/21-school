#include "WrongCat.hpp"
#include <iostream>

WrongCat::WrongCat() {
	std::cout << "WrongCat type " << type << " constructor called" << std::endl;
	type = "WrongCat";
}

WrongCat::WrongCat(WrongCat& other) {
	std::cout << "WrongCat copy constructor called" << std::endl;
	type = other.type;
}

WrongCat::~WrongCat() {
	std::cout << "WrongCat destructor called" << std::endl;
}

void	WrongCat::makeSound() const {
	std::cout << "WrongCat makes sound: moooooh!." << std::endl;
}


WrongCat&	WrongCat::operator =(WrongCat& other) {
	std::cout << "WrongCat assignment operator called" << std::endl;
	if (this == &other)
		return *this;
	type = other.type;
	return *this;
}
