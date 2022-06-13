#ifndef WRONGANIMAL_H
# define WRONGANIMAL_H

# include <string>

class WrongAnimal {
public:
	WrongAnimal();
	WrongAnimal(WrongAnimal&);
	~WrongAnimal();

	const std::string&	getType() const;

	void			makeSound() const;
	
	WrongAnimal&	operator =(WrongAnimal&);

protected:
	std::string type;
};

#endif
