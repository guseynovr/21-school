#include "HumanB.hpp"
#include <iostream>

HumanB::HumanB(std::string name) {
	this->_name = name;
	this->_weapon = 0;
}

void	HumanB::setWeapon(Weapon& weapon) {
	this->_weapon = &weapon;
}

void	HumanB::attack() {
	std::string	wp;

	if (this->_weapon)
		wp = _weapon->getType();
	else
		wp = "hands";
	std::cout << _name << " attacks with his " << wp << std::endl;
}
