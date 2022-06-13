#include "Zombie.hpp"
#include <iostream>

Zombie::Zombie() {};

Zombie::Zombie(std::string name) {
	this->_name = name;
}

Zombie::~Zombie(void) {
	std::cout << _name << " has died" << std::endl;
}

void	Zombie::set_name(std::string name) {
	this->_name = name;
}

void	Zombie::announce(void) {
	std::cout << _name << " BraiiiiiiinnnzzzZ..." << std::endl;
}
