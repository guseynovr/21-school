#include "Cat.hpp"
#include <iostream>

Cat::Cat() {
	std::cout << "Cat type " << type << " constructor called" << std::endl;
	type = "Cat";
	brain = new Brain();
}

Cat::Cat(const Cat& other) : Animal(other.type) {
	std::cout << "Cat copy constructor called" << std::endl;
	brain = new Brain(*other.brain);
}

Cat::~Cat() {
	std::cout << "Cat destructor called" << std::endl;
	delete brain;
}

const Brain*	Cat::getBrain() const {
	return brain;
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
