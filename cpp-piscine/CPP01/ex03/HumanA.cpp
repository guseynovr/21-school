#include "HumanA.hpp"
#include <iostream>

HumanA::HumanA(std::string name, Weapon &weapon) : _weapon(weapon) {
	this->_name = name;
	// this->_weapon = weapon
}

void	HumanA::attack() {
	std::cout << _name << " attacks with his " << _weapon.getType()
		<< std::endl;
}
