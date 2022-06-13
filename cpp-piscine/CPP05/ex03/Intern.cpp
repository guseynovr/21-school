#include "Intern.hpp"
#include "cctype"

Intern::Intern() {
	funcs[0] = &Intern::makePPF;
	funcs[1] = &Intern::makeRRF;
	funcs[2] = &Intern::makeSCF;
	fnames[0] = PP_NAME;
	fnames[1] = RR_NAME;
	fnames[2] = SC_NAME;
}

Intern::Intern(const Intern& other) {
	funcs[0] = other.funcs[0];
	funcs[1] = other.funcs[1];
	funcs[2] = other.funcs[2];
	fnames[0] = other.fnames[0];
	fnames[1] = other.fnames[1];
	fnames[2] = other.fnames[2];
}

Intern::~Intern() {}

std::string	loweredStr(std::string s) {
	for (int i = 0; s[i]; i++)
		s[i] = std::tolower(s[i]);
	return s;
}

int		Intern::getId(std::string name) {
	int i = -1;
	while (++i < FUNCS_SIZE) {
		if (name == fnames[i])
			break;
	}
	return i;
}

Form*	Intern::makeForm(std::string name, std::string target) {
	int	id = getId(loweredStr(name));

	if (id != FUNCS_SIZE) {
		std::cout << "Intern makes form " << loweredStr(name) << std::endl;
		return (this->*funcs[id])(target);
	}
	std::cout << "No form for name " << name << std::endl;
	return NULL;
}

Form*	Intern::makePPF(std::string target) {
	return new PresidentialPardonForm(target);
}

Form*	Intern::makeRRF(std::string target) {
	return new RobotomyRequestForm(target);
}

Form*	Intern::makeSCF(std::string target) {
	return new ShrubberyCreationForm(target);
}

Intern& Intern::operator=(const Intern& other) {
	if (this == &other)
		return *this;
	funcs[0] = other.funcs[0];
	funcs[1] = other.funcs[1];
	funcs[2] = other.funcs[2];
	fnames[0] = other.fnames[0];
	fnames[1] = other.fnames[1];
	fnames[2] = other.fnames[2];
	return *this;
}
