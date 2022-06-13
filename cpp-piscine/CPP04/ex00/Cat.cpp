#include "Cat.hpp"
#include <iostream>

Cat::Cat() {
	std::cout << "Cat type " << type << " constructor called" << std::endl;
	type = "Cat";
}

Cat::Cat(Cat& other) : Animal(other.type) {
	std::cout << "Cat copy constructor called" << std::endl;
}

Cat::~Cat() {
	std::cout << "Cat destructor called" << std::endl;
}

void	Cat::makeSound() const {
	std::cout << "cat makes sound: meow." << std::endl;
}

Cat&	Cat::operator =(Cat& other) {
	std::cout << "Cat assignment operator called" << std::endl;
	if (this == &other)
		return *this;
	type = other.type;
	return *this;
}
