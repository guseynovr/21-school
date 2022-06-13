#include "ClapTrap.hpp"
#include <iostream>
#include <limits>

ClapTrap::ClapTrap()
	: hitPoints(CLAP_HP),
	energyPoints(CLAP_EP),
	attackDamage(CLAP_DMG) {}

ClapTrap::ClapTrap(std::string name)
	: name(name), hitPoints(CLAP_HP),
	energyPoints(CLAP_EP),
	attackDamage(CLAP_DMG) {}

ClapTrap::ClapTrap(ClapTrap& other)
	: name(other.name),
	hitPoints(other.hitPoints),
	energyPoints(other.energyPoints),
	attackDamage(other.attackDamage) {}

ClapTrap::~ClapTrap() {}

const std::string&	ClapTrap::getName() const {
	return name;
}

unsigned int	ClapTrap::getAttackDamage() const {
	if (lastAttack)
		return attackDamage;
	return 0;
}

void	ClapTrap::setAttackDamage(unsigned int amount) {
	attackDamage = amount;
}

void	ClapTrap::attack(std::string const & target) {
	if (attackDamage > energyPoints) {
		std::cout << "Claptrap " << name
			<< " doesn't has enough energy points to attack." << std::endl;
		lastAttack = false;
	}
	else {
		energyPoints -= attackDamage;
		lastAttack = true;
		std::cout << "ClapTrap " << name << " attacks " << target
			<< ", causing " << attackDamage << " points of damage!" 
			<< " Now has " << energyPoints << " energy points." << std::endl;
	}
}

void	ClapTrap::takeDamage(unsigned int amount) {
	// std::cout << name << " takeDamage: " << amount << ", hitPoints: "
	// 	<< hitPoints << std::endl;
	if (hitPoints > amount)
		hitPoints -= amount;
	else
		hitPoints = 0;
	std::cout << "ClapTrap " << name << " takes "
		<< amount << " points of damage!" << " Now has "
		<< hitPoints << " hitpoints."<< std::endl;
}

void	ClapTrap::beRepaired(unsigned int amount) {
	if (hitPoints + amount > std::numeric_limits<unsigned int>::max())
		hitPoints = std::numeric_limits<unsigned int>::max();
	else
		hitPoints = hitPoints + amount;
	std::cout << "ClapTrap " << name << " is repaired for " << amount
		<< " hit points!" << " Now has " << hitPoints << " hitpoints."
		<< std::endl;
}

ClapTrap&	ClapTrap::operator =(const ClapTrap& other) {
	if (this == &other)
		return *this;
	name = other.name;
	hitPoints = other.hitPoints;
	energyPoints = other.energyPoints;
	attackDamage = other.attackDamage;
	return *this;
}
