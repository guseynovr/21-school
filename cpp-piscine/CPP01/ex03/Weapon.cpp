#include "Weapon.hpp"

Weapon::Weapon() {}

Weapon::Weapon(std::string type) {
	this->_type = type;
}

void	Weapon::setType(std::string type) {
	this->_type = type;
}

const std::string&	Weapon::getType() const {
	return	this->_type;
}
