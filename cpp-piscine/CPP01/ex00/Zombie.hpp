#ifndef ZOMBIE_H
# define ZOMBIE_H

#include <string>

class Zombie {
public:
	Zombie();
	Zombie(std::string);
	~Zombie();

	void	announce(void);
	void	set_name(std::string);
private:
	std::string	_name;
};

#endif
