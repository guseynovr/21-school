#include "Ice.hpp"
#include <iostream>

Ice::Ice() : AMateria("ice") {}

Ice::Ice(const Ice& other) : AMateria(other.getType()) {}

Ice::~Ice() {}

Ice*	Ice::clone() const {
	return new Ice();
}

void	Ice::use(ICharacter& target) {
	std::cout << "* Shoots an ice bolt ❄️  at " << target.getName() << " *"
		<< std::endl;
}

Ice&	Ice::operator=(const Ice& other) {
	(void) other;
	return *this;
}
