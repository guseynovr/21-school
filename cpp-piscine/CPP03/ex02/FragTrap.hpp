#ifndef FRAGTRAP_H
# define FRAGTRAP_H

#include "ClapTrap.hpp"

# define FRAG_HP 100
# define FRAG_EP 100
# define FRAG_DMG 30

class FragTrap : public ClapTrap {
public:
	FragTrap();
	FragTrap(std::string name);
	FragTrap(ClapTrap&);
	~FragTrap();

	void		attack(std::string const & target);
	void		highFivesGuys();

	FragTrap&	operator =(FragTrap&);

private:
	void		initDefaultValues();
};

#endif
