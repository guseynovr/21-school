#include "FragTrap.hpp"
#include <iostream>

FragTrap::FragTrap() {
	std::cout << "FragTrap default constructor called" << std::endl;
	initDefaultValues();
}

FragTrap::FragTrap(std::string name) : ClapTrap(name) {
	std::cout << "FragTrap " << name << " constructor called" << std::endl;
	initDefaultValues();
}

FragTrap::FragTrap(ClapTrap& other) : ClapTrap(other) {
	std::cout << "FragTrap copy constructor called" << std::endl;
	initDefaultValues();
}

FragTrap::~FragTrap() {
	std::cout << "FragTrap " << name << " destructor called" << std::endl;
}

void	FragTrap::attack(std::string const & target) {
	if (attackDamage > energyPoints) {
		std::cout << "FragTrap " << name
			<< " doesn't has enough energy points to attack." << std::endl;
		lastAttack = false;
	}
	else {
		energyPoints -= attackDamage;
		lastAttack = true;
		std::cout << "FragTrap " << name << " attacks " << target
			<< ", causing " << attackDamage << " points of damage!" 
			<< " Now has " << energyPoints << " energy points." << std::endl;
	}
}

void	FragTrap::highFivesGuys() {
	std::cout << "FragTrap " << name << " tries to give a high five."
		<< std::endl;
}

FragTrap&	FragTrap::operator =(FragTrap& other) {
	if (this == &other)
		return *this;
	name = other.name;
	hitPoints = other.hitPoints;
	energyPoints = other.energyPoints;
	attackDamage = other.attackDamage;
	return *this;
}

void	FragTrap::initFragHP() {
	hitPoints = FRAG_HP;
}

void	FragTrap::initFragEP() {
	energyPoints = FRAG_EP;
}

void	FragTrap::initFragDmg() {
	attackDamage = FRAG_DMG;
}

void	FragTrap::initDefaultValues() {
	initFragHP();
	initFragEP();
	initFragDmg();
}
