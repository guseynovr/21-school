#ifndef CURE_H
# define CURE_H

# include "ICharacter.hpp"
# include "AMateria.hpp"

class Cure : public AMateria {
public:
	Cure();
	Cure(const Cure&);
	~Cure();

	Cure*	clone() const;
	void	use(ICharacter& target);

	Cure&	operator=(const Cure& other);
};

#endif
