#ifndef DIAMONDTRAP_H
# define DIAMONDTRAP_H

#include "FragTrap.hpp"
#include "ScavTrap.hpp"

class DiamondTrap : public FragTrap, public ScavTrap{
public:
	DiamondTrap();
	DiamondTrap(std::string name);
	DiamondTrap(DiamondTrap&);
	~DiamondTrap();
	
	void	whoAmI();
	void	attack(std::string const & target);

protected:
	void		initDefaultValues();

private:
	std::string name;
};

#endif
