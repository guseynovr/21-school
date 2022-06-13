#include <iostream>
#include "Form.hpp"
#include "Bureaucrat.hpp"

int main() {
	try {
		Form	a("A", 0, 1);
		std::cout << a << std::endl;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	try {
		Form	a("A", 200, 1);
		std::cout << a << std::endl;
	} catch (std::exception& e) {
		std::cout << e.what() << std::endl;
	}
	{
		Form		f("F", 15, 10);
		Bureaucrat	b("Suit", 10);

		std::cout << f << std::endl;
		b.signForm(f);
		std::cout << f << std::endl;
	}
	{
		Form		a("A", 1, 10);
		Bureaucrat	b("Suit", 10);

		std::cout << a << std::endl;
		b.signForm(a);
		std::cout << a << std::endl;
	}
	{
		Form		a("A", 1, 10);
		Bureaucrat	b("Suit", 10);

		std::cout << a << std::endl;
		b.signForm(a);
	}
}
