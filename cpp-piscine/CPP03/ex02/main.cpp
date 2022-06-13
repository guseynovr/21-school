#include "FragTrap.hpp"
#include "ClapTrap.hpp"

int main() {
	FragTrap	john("John");
	FragTrap	mike("Mike");

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
