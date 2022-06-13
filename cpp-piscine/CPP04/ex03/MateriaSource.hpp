#ifndef MATERIASOURCE_H
# define MATERIASOURCE_H

# include "IMateriaSource.hpp"
# include "Ice.hpp"
# include "Cure.hpp"
# include <string>

# define M_CAP 4

class MateriaSource : public IMateriaSource {
public:
	MateriaSource();
	MateriaSource(const MateriaSource& other);
	~MateriaSource();

	void		learnMateria(AMateria*);
	AMateria*	createMateria(std::string const & type);

	MateriaSource&	operator=(const MateriaSource& other);

private:
	AMateria*	materias[M_CAP];
};

#endif
