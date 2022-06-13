#ifndef DOG_H
# define DOG_H

# include "Animal.hpp"
# include "Brain.hpp"

class Dog : public Animal {
public:
	Dog();
	Dog(const Dog&);
	~Dog();
	
	const Brain*	getBrain() const;

	void	makeSound() const;

	Dog&	operator =(Dog&);

private:
	Brain*	brain;
};

#endif
