#ifndef WEAPON_H
# define WEAPON_H

# include <string>

class Weapon {
public:
	Weapon();
	Weapon(std::string);

	void				setType(std::string);
	const std::string&	getType() const;

private:
	std::string	_type;
};

#endif
