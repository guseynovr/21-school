#ifndef CAT_H
# define CAT_H

# include "Animal.hpp"

class Cat : public Animal {
public:
	Cat();
	Cat(Cat&);
	~Cat();

	void	makeSound() const;

	Cat&	operator =(Cat&);
};

#endif
