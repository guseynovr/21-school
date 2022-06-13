#include "Character.hpp"
#include <iostream>

/* Character::Character() : name("N/A") {
	for (int i = 0; i < INV_CAP; i++)
		inventory[i] = 0;
} */

Character::Character(std::string name) : name(name) {
	for (int i = 0; i < INV_CAP; i++)
		inventory[i] = 0;
}

Character::Character(const Character& other) : name(other.name) {
	for (int i = 0; i < INV_CAP; i++) {
		if (other.inventory[i])
			inventory[i] = other.inventory[i]->clone();
		else
			inventory[i] = 0;
	}
}

Character::~Character() {
	for (int i = 0; i < INV_CAP; i++)
		delete inventory[i];
}

std::string const & Character::getName() const {
	return name;
}
	
void Character::equip(AMateria* m) {
	for (int i = 0; i < INV_CAP; i++) {
		if (inventory[i] == 0) {
			inventory[i] = m;
			break;
		}
	}
}

void Character::unequip(int idx) {
	inventory[idx] = 0;
}

void Character::use(int idx, ICharacter& target) {
	if (idx >= 0 && idx < INV_CAP && inventory[idx])
		inventory[idx]->use(target);
	else
		std::cout << "No materia at index " << idx << " in inventory"
			<< std::endl;
}

Character&	Character::operator=(const Character& other) {
	if (this == &other)
		return *this;
	for (int i = 0; i < INV_CAP; i++) {
		delete inventory[i];
		if (other.inventory[i])
			inventory[i] = other.inventory[i]->clone();
		else
			inventory[i] = 0;
	}
	name = other.name;
	return *this;
}
