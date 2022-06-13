#ifndef WRONGCAT_H
# define WRONGCAT_H

# include "WrongAnimal.hpp"

class WrongCat : public WrongAnimal {
public:
	WrongCat();
	WrongCat(WrongCat&);
	~WrongCat();

	void	makeSound() const;

	WrongCat&	operator =(WrongCat&);
};

#endif
