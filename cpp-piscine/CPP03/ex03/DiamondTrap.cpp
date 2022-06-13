#include "DiamondTrap.hpp"
#include <iostream>

DiamondTrap::DiamondTrap() {
	std::cout << "DiamondTrap default contructor called" << std::endl;
}

DiamondTrap::DiamondTrap(std::string name)
	: ClapTrap(name + "_clap_name"),
	name(name)
{
	initDefaultValues();
	// std::cout << ">>>INIT: " << hitPoints << " " << energyPoints << " "
	// 	<< attackDamage << std::endl;
	std::cout << "DiamondTrap " << name << " contructor called" << std::endl;
}

DiamondTrap::DiamondTrap(DiamondTrap& other)
	: ClapTrap(other.name + "_clap_name"),
	name(other.name)
{
	initDefaultValues();
	std::cout << "DiamondTrap copy destructor called" << std::endl;
}

DiamondTrap::~DiamondTrap() {
	std::cout << "DiamondTrap " << name << " destructor called" << std::endl;
}

void	DiamondTrap::attack(std::string const & target) {
	ScavTrap::attack(target);
}

void	DiamondTrap::whoAmI() {
	std::cout << "whoAmI: " << name
		<< ", ClapTrap::name: " << ClapTrap::name << std::endl;
}

void	DiamondTrap:: initDefaultValues() {
	initFragHP();
	initScavEP();
	initFragDmg();
}
