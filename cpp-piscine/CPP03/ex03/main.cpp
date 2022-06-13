#include "DiamondTrap.hpp"

#include "ScavTrap.hpp"
#include "FragTrap.hpp"

int main() {
	DiamondTrap	john("John");
	DiamondTrap	mike("Mike");

	john.attack(mike.getName());
	mike.takeDamage(john.getAttackDamage());

	// mike.setAttackDamage(2);
	mike.attack(john.getName());
	john.takeDamage(mike.getAttackDamage());
	john.beRepaired(20);

	// mike.setAttackDamage(9);
	mike.attack(john.getName());
	john.takeDamage(mike.getAttackDamage());

	john.whoAmI();
	john.highFivesGuys();
	john.guardGate();
}
