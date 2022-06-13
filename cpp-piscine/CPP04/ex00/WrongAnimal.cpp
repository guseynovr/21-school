#include "WrongAnimal.hpp"
#include <iostream>

WrongAnimal::WrongAnimal() {
	std::cout << "WrongAnimal default contructor called" << std::endl;
}

WrongAnimal::WrongAnimal(WrongAnimal& other) : type(other.type) {
	std::cout << "WrongAnimal copy contructor called" << std::endl;
}

WrongAnimal::~WrongAnimal() {
	std::cout << "WrongAnimal destructor called" << std::endl;
}

const std::string&	WrongAnimal::getType() const {
	return type;
}

void	WrongAnimal::makeSound() const {
	std::cout << "WrongAnimal makes sound: undefined sound" << std::endl;
}

WrongAnimal&	WrongAnimal::operator =(WrongAnimal& other) {
	std::cout << "WrongAnimal assignment operator called" << std::endl;
	if (this == &other)
		return *this;
	type = other.type;
	return *this;
}
