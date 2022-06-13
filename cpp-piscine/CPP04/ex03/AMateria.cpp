#include "AMateria.hpp"
#include <iostream>

AMateria::AMateria(std::string const & type) : type(type) {}

AMateria::AMateria(const AMateria& other) : type(other.type) {}

AMateria::~AMateria() {}

std::string const &	AMateria::getType() const {
	return type;
}

void	AMateria::use(ICharacter& target) {
	(void) target;
}

AMateria&	AMateria::operator=(const AMateria& other) {
	(void) other;
	return *this;
}
