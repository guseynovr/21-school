#ifndef ICE_H
# define ICE_H

# include "ICharacter.hpp"
# include "AMateria.hpp"

class Ice : public AMateria {
public:
	Ice();
	Ice(const Ice&);
	~Ice();

	Ice*	clone() const;
	void	use(ICharacter& target);

	Ice&	operator=(const Ice& other);
};

#endif
