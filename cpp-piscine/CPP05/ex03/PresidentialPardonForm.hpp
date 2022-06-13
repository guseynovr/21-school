#ifndef PRESIDENTIAL_PARDON_FORM_H
# define PRESIDENTIAL_PARDON_FORM_H

# define PPF_SIGN 25
# define PPF_EXEC 5
# define PPF_NAME "PresidentialPardonForm"

# include "Form.hpp"

class PresidentialPardonForm : public Form {
public:
	PresidentialPardonForm(const std::string& target);
	PresidentialPardonForm(const PresidentialPardonForm& pform);
	virtual ~PresidentialPardonForm();

	PresidentialPardonForm&	operator=(const PresidentialPardonForm& other);

private:
	std::string	target;

	PresidentialPardonForm();

	virtual void	exec() const;
};

#endif
