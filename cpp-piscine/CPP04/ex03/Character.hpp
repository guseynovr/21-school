#ifndef CHARACTER_H
# define CHARACTER_H

# include "ICharacter.hpp"
# include "AMateria.hpp"
# include <string>

# define INV_CAP 4

class Character : public ICharacter {
public:
	// Character();
	Character(std::string name);
	Character(const Character&);
	~Character();

	std::string const & getName() const;
	
	void equip(AMateria* m);
	void unequip(int idx);
	void use(int idx, ICharacter& target);

	Character&	operator=(const Character&);

private:
	std::string	name;
	AMateria*	inventory[INV_CAP];
};

#endif
