#include "Bureaucrat.hpp"
#include <iostream>

int main() {
	Bureaucrat	kate("Kate", 1);
	std::cout << kate << std::endl;
	try {
		kate.upgrade();
	}
	catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	kate.downgrade();
	kate.downgrade();
	kate.downgrade();
	kate.downgrade();
	std::cout << kate << std::endl;

	try {
		Bureaucrat tooHigh("High", 0);
		std::cout << tooHigh << std::endl;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}

	try {
		Bureaucrat	bill("Bill", 151);
		std::cout << bill << std::endl;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	Bureaucrat	bill("Bill", 150);
	std::cout << bill << std::endl;
	try {
		bill.downgrade();
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	try {
		bill.downgrade();
	} catch (Bureaucrat::GradeTooHighException& e) {
		std::cout << "GradeTooHigh: " << e.what() << std::endl;
	} catch (Bureaucrat::GradeTooLowException& e) {
		std::cout << "GradeTooLow: " << e.what() << std::endl;
	} catch (std::exception& e) {
		std::cout << "exception: " << e.what() << std::endl;
	}
}
