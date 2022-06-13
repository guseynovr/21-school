#include "ShrubberyCreationForm.hpp"
#include <fstream>

ShrubberyCreationForm::ShrubberyCreationForm()
:	Form(), target("no target") {}

ShrubberyCreationForm::ShrubberyCreationForm(const std::string& target)
:	Form(SCF_NAME, SCF_SIGN, SCF_EXEC), target(target) {}

ShrubberyCreationForm::ShrubberyCreationForm(const ShrubberyCreationForm& rform)
:	Form(SCF_NAME, SCF_SIGN, SCF_EXEC), target(rform.target) {}

ShrubberyCreationForm::~ShrubberyCreationForm() {}

void	ShrubberyCreationForm::exec() const {
	std::ofstream	file;

	file.open(target + "_shrubbery");
	if (!file.is_open()) {
		std::cout << "Unable to open file\n";
		return; 
	}
	file << "      v .   ._, |_  .,\n";
	file << "   `-._\\/  .  \\ /    |/_\n";
	file << "       \\  _\\, y | \\//\n";
	file << " _\\_.___\\, \\/ -.\\||\n";
	file << "   `7-,--.`._||  / / ,\n";
	file << "   /'     `-. `./ / |/_.'\n";
	file << "             |    |//\n";
	file << "             |_    /\n";
	file << "             |-   |\n";
	file << "             |   =|\n";
	file << "             |    |\n";
	file << "------------/ ,  . \\--------._\n";
	file.close();
}

ShrubberyCreationForm&	ShrubberyCreationForm::operator=(
const ShrubberyCreationForm& other) {
	if (this == &other)
		return *this;
	Form::operator=(other);
	target = other.target;
	return *this;
}
