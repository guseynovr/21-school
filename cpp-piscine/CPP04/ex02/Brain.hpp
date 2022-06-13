#ifndef BRAIN_H
# define BRAIN_H

# include <string>

# define IDEAS_SIZE 100

class Brain {
public:
	Brain();
	Brain(Brain&);
	~Brain();

	Brain&	operator =(Brain&);

private:
	std::string	ideas[IDEAS_SIZE];
};

#endif
