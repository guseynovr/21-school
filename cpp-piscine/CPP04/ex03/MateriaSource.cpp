#include "MateriaSource.hpp"

AMateria*	newMateria(std::string const & type) {
	if (type == "ice")
		return new Ice();
	else if (type == "cure")
		return new Cure();
	return NULL;
}

MateriaSource::MateriaSource() {
	for (int i = 0; i < M_CAP; i++)
		materias[i] = 0;
}

MateriaSource::MateriaSource(const MateriaSource& other) {
	for (int i = 0; i < M_CAP; i++)
		materias[i] = newMateria(other.materias[i]->getType());
}

MateriaSource::~MateriaSource() {
	for (int i = 0; i < M_CAP; i++)
		delete materias[i];
}

void	MateriaSource::learnMateria(AMateria* m) {
	/* AMateria*	learned; */
	int			idx = -1;

	if (!m)
		return;
	while (++idx < M_CAP) {
		if (materias[idx] == 0)
			break;
	}
	if (idx == M_CAP)
		return;
	/* learned = newMateria(m->getType()); 
	if (!learned)
		return;
	materias[idx] = learned; */
	materias[idx] = m;
}

AMateria*	MateriaSource::createMateria(std::string const & type) {
	int	idx = -1;

	while (++idx < M_CAP) {
		if (materias[idx] && materias[idx]->getType() == type)
			break;
	}
	if (idx == M_CAP)
		return NULL;
	return newMateria(materias[idx]->getType());
}

MateriaSource&	MateriaSource::operator=(const MateriaSource& other) {
	if (this == &other)
		return *this;
	for (int i = 0; i < M_CAP; i++) {
		delete materias[i];
		materias[i] = newMateria(other.materias[i]->getType());
	}
	return *this;
}
