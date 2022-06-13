#ifndef ROBOTOMY_REQUEST_FORM_H
# define ROBOTOMY_REQUEST_FORM_H

# define RRF_SIGN 72
# define RRF_EXEC 45
# define RRF_NAME "RobotomyRequestForm"

# include "Form.hpp"

class RobotomyRequestForm : public Form {
public:
	RobotomyRequestForm(const std::string& target);
	RobotomyRequestForm(const RobotomyRequestForm& rform);
	virtual ~RobotomyRequestForm();

	RobotomyRequestForm&	operator=(const RobotomyRequestForm& other);

private:
	std::string	target;

	RobotomyRequestForm();

	virtual void	exec() const;
};

#endif
