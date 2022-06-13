#ifndef KAREN_H
# define KAREN_H

#include <string>

class Karen {

public:
	Karen();

	void	complain(std::string level);

private:
	void		debug();
	void		info();
	void		warning();
	void		error();

	std::string	_level_names[4];
	void		(Karen::*f[4])();
	int			get_level(std::string level);
};

#endif
