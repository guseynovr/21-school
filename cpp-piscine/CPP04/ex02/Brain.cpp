#include "Brain.hpp"
#include <iostream>

Brain::Brain() {
	std::cout << "Brain default constructor called" << std::endl;
}
Brain::Brain(Brain& other) {
	std::cout << "Brain copy constructor called" << std::endl;
	for (int i = 0; i < IDEAS_SIZE; i++)
		ideas[i] = other.ideas[i];
}
Brain::~Brain() {
	std::cout << "Brain destructor called" << std::endl;
}

Brain&	Brain::operator =(Brain& other) {
	std::cout << "Brain assignment operator called" << std::endl;
	if (this == &other)
		return *this;
	for (int i = 0; i < IDEAS_SIZE; i++)
		ideas[i] = other.ideas[i];
	return *this;
}
