#ifndef HUMANB_H
# define HUMANB_H

# include "Weapon.hpp"

class HumanB {
public:
	HumanB(std::string);

	void	setWeapon(Weapon&);
	void	attack();

private:
	std::string	_name;
	Weapon*		_weapon;
};

#endif
