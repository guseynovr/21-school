#include "ScavTrap.hpp"
#include "ClapTrap.hpp"

int main() {
	ScavTrap	john("John");
	ScavTrap	mike("Mike");

	john.attack(mike.getName());
	mike.takeDamage(john.getAttackDamage());

	mike.setAttackDamage(2);
	mike.attack(john.getName());
	john.takeDamage(mike.getAttackDamage());
	john.beRepaired(20);

	mike.setAttackDamage(9);
	mike.attack(john.getName());
	john.takeDamage(mike.getAttackDamage());
}
