#ifndef DOG_H
# define DOG_H

# include "Animal.hpp"

class Dog : public Animal {
public:
	Dog();
	Dog(Dog&);
	~Dog();

	void	makeSound() const;

	Dog&	operator =(Dog&);
};

#endif
