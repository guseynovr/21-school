#include "Dog.hpp"
#include <iostream>

Dog::Dog() {
	std::cout << "Dog type " << type << " constructor called" << std::endl;
	type = "Dog";
	brain = new Brain();
}

Dog::Dog(const Dog& other) {
	std::cout << "Dog copy constructor called" << std::endl;
	type = other.type;
	brain = new Brain(*other.brain);
	// brain = other.brain;
}

Dog::~Dog() {
	std::cout << "Dog destructor called" << std::endl;
	delete brain;
}

const Brain*	Dog::getBrain() const {
	return brain;
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
