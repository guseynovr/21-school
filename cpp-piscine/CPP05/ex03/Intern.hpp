#ifndef INTERN_H
# define INTERN_H

# define FUNCS_SIZE 3
# define PP_NAME "presidential pardon"
# define RR_NAME "robotomy request"
# define SC_NAME "shrubbery creation"

# include "PresidentialPardonForm.hpp"
# include "RobotomyRequestForm.hpp"
# include "ShrubberyCreationForm.hpp"

class Intern {

typedef Form* (Intern::*makeFunc)(std::string);

public:
	Intern();
	Intern(const Intern& other);
	~Intern();

	Form*	makeForm(std::string name, std::string target);

	Intern&	operator=(const Intern& other);

private:
	std::string	fnames[FUNCS_SIZE];

	// Form*	(Intern::*funcs[FUNCS_SIZE])(std::string);
	makeFunc	funcs[FUNCS_SIZE];
	Form*		makePPF(std::string target);
	Form*		makeRRF(std::string target);
	Form*		makeSCF(std::string target);
	int			getId(std::string name);
};

#endif
