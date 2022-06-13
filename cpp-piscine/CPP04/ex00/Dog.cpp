#include "Dog.hpp"
#include <iostream>

Dog::Dog() {
	std::cout << "Dog type " << type << " constructor called" << std::endl;
	type = "Dog";
}

Dog::Dog(Dog& other) {
	std::cout << "Dog copy constructor called" << std::endl;
	type = other.type;
}

Dog::~Dog() {
	std::cout << "Dog destructor called" << std::endl;
}

void	Dog::makeSound() const {
	std::cout << "Dog makes sound: Woof!" << std::endl;
}

Dog&	Dog::operator =(Dog& other) {
	std::cout << "Dog assignment operator called" << std::endl;
	if (this == &other)
		return *this;
	type = other.type;
	return *this;
}
