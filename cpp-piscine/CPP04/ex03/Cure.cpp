#include "Cure.hpp"
#include <iostream>

Cure::Cure() : AMateria("cure") {}

Cure::Cure(const Cure& other) : AMateria(other.getType()) {}

Cure::~Cure() {}

Cure*	Cure::clone() const {
	return new Cure();
}

void	Cure::use(ICharacter& target) {
	std::cout << "* heals 🚑 " << target.getName() << "’s wounds *" << std::endl;
}

Cure&	Cure::operator=(const Cure& other) {
	(void) other;
	return *this;
}
