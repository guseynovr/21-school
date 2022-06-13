#ifndef CAT_H
# define CAT_H

# include "Animal.hpp"
# include "Brain.hpp"

class Cat : public Animal {
public:
	Cat();
	Cat(const Cat&);
	~Cat();

	const Brain*	getBrain() const;

	void	makeSound() const;

	Cat&	operator =(Cat&);

private:
	Brain*	brain;
};

#endif
