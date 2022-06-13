#include "PresidentialPardonForm.hpp"

PresidentialPardonForm::PresidentialPardonForm()
:	Form(), target("no target") {}

PresidentialPardonForm::PresidentialPardonForm(const std::string& target)
:	Form(PPF_NAME, PPF_SIGN, PPF_EXEC), target(target) {}

PresidentialPardonForm::PresidentialPardonForm(const PresidentialPardonForm& pform)
:	Form(PPF_NAME, PPF_SIGN, PPF_EXEC), target(pform.target) {}

PresidentialPardonForm::~PresidentialPardonForm() {}

void	PresidentialPardonForm::exec() const {
	std::cout << target << " has been pardoned by Zafod Beeblebrox.\n";
}

PresidentialPardonForm&	PresidentialPardonForm::operator=(
const PresidentialPardonForm& other) {
	if (this == &other)
		return *this;
	Form::operator=(other);
	target = other.target;
	return *this;
}
