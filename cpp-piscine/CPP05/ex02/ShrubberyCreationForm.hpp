#ifndef SHRUBBERY_CREATION_FORM_H
# define SHRUBBERY_CREATION_FORM_H

# define SCF_SIGN 145
# define SCF_EXEC 137
# define SCF_NAME "ShrubberyCreationForm"

# include "Form.hpp"

class ShrubberyCreationForm : public Form {
public:
	ShrubberyCreationForm(const std::string& target);
	ShrubberyCreationForm(const ShrubberyCreationForm& rform);
	virtual ~ShrubberyCreationForm();

	ShrubberyCreationForm&	operator=(const ShrubberyCreationForm& other);

private:
	std::string	target;

	ShrubberyCreationForm();

	virtual void	exec() const;
};

#endif
