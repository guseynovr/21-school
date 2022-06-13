#ifndef SCAVTRAP_H
# define SCAVTRAP_H

#include "ClapTrap.hpp"

# define SCAV_HP 100
# define SCAV_EP 50
# define SCAV_DMG 20

class ScavTrap : public virtual ClapTrap {
public:
	ScavTrap();
	ScavTrap(std::string name);
	ScavTrap(ClapTrap&);
	~ScavTrap();

	void		attack(std::string const & target);
	void		guardGate();

	ScavTrap&	operator =(ScavTrap&);
	
protected:
	void		initDefaultValues();
	void		initScavHP();
	void		initScavEP();
	void		initScavDmg();
};

#endif
