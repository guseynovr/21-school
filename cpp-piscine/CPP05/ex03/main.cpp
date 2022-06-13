#include <iostream>
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"
#include "Intern.hpp"

int main() {
	Intern	intern;

	Form*	pp = intern.makeForm("Presidential Pardon", "Someone");
	Form*	rr = intern.makeForm("Robotomy request", "Robocop");
	Form*	sc = intern.makeForm("Shrubbery creation", "Backyard");
	Form*	err = intern.makeForm("kjsdashf", "error");
	(void) err;

	Bureaucrat	b("James", 1);
	b.signForm(*pp);
	b.signForm(*rr);
	b.signForm(*sc);

	b.executeForm(*pp);
	b.executeForm(*rr);
	b.executeForm(*sc);

	delete pp;
	delete rr;
	delete sc;
}
