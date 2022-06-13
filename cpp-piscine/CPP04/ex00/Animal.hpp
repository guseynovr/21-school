#ifndef	ANIMAL_H
# define ANIMAL_H

# include <string>

class Animal {
public:
	Animal();
	Animal(std::string type);
	Animal(Animal&);
	virtual ~Animal();

	const std::string&	getType() const;
	
	virtual void	makeSound() const;
	
	Animal&	operator =(Animal&);

protected:
	std::string type;
};

#endif
