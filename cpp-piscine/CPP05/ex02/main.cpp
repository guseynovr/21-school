#include <iostream>
#include "PresidentialPardonForm.hpp"
#include "RobotomyRequestForm.hpp"
#include "ShrubberyCreationForm.hpp"
#include "Bureaucrat.hpp"

int main() {
	// Form from("asd", 1, 1);
	std::cout << "\n----------PRESIDENTIAL PARDON FORM----------\n\n";
	PresidentialPardonForm	pardonForm("smbd");
	Bureaucrat				john("John", 26);
	Bureaucrat				mike("Mike", 5);

	john.executeForm(pardonForm);
	mike.executeForm(pardonForm);
	john.signForm(pardonForm);
	mike.signForm(pardonForm);
	mike.executeForm(pardonForm);

	std::cout << "\n-----------ROBOTOMY REQUEST FORM------------\n\n";
	RobotomyRequestForm		roboform("Robocop");

	john.executeForm(roboform);
	mike.executeForm(roboform);
	john.signForm(roboform);
	mike.signForm(roboform);
	mike.executeForm(roboform);

	std::cout << "\n-----------SHRUBBERY CREATION FORM----------\n\n";
	ShrubberyCreationForm		shrubbery("Backyard");

	john.executeForm(shrubbery);
	mike.executeForm(shrubbery);
	john.signForm(shrubbery);
	mike.signForm(shrubbery);
	mike.executeForm(shrubbery);
	
}
