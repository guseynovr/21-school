#ifndef CLAPTRAP_H
# define CLAPTRAP_H

# include <string>

# define CLAP_HP 10
# define CLAP_EP 10
# define CLAP_DMG 0

class ClapTrap {
public:
	ClapTrap();
	ClapTrap(std::string name);
	ClapTrap(ClapTrap&);
	virtual ~ClapTrap();

	unsigned int		getAttackDamage() const;
	void				setAttackDamage(unsigned int);
	const std::string&	getName() const;

	void				attack(std::string const & target);
	void				takeDamage(unsigned int amount);
	void				beRepaired(unsigned int amount);

	ClapTrap& 			operator =(const ClapTrap&);

protected:
	std::string			name;
	unsigned int		hitPoints;
	unsigned int		energyPoints;
	unsigned int		attackDamage;
	bool				lastAttack;
};

#endif
