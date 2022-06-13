#ifndef BUREAUCRAT_H
# define BUREAUCRAT_H

# define GR_HIGH	1
# define GR_LOW		150

# define GR_HIGH_DESC	"Grade too high exception"
# define GR_LOW_DESC	"Grade too low exception"

# include <string>
# include <iostream>

#include "Form.hpp"
class	Form;

class	Bureaucrat {
public:
	Bureaucrat(const std::string name, const int grade);
	Bureaucrat(const Bureaucrat& other);
	~Bureaucrat();

	const std::string&	getName() const;
	const int&			getGrade() const;

	void	upgrade();
	void	downgrade();
	void	signForm(Form&) const;

	Bureaucrat& operator=(const Bureaucrat& other);

	class	GradeTooHighException : public std::exception {
	public:
		GradeTooHighException() throw();
		virtual ~GradeTooHighException() throw();
		virtual const char* what() const throw();
	private:
		const std::string	descr;
	};

	class	GradeTooLowException : public std::exception {
	public:
		GradeTooLowException() throw();
		virtual ~GradeTooLowException() throw();
		virtual const char* what() const throw();
	private:
		const std::string	descr;
	};

private:
	const std::string	name;
	int					grade;

	Bureaucrat(); 

	void	setGrade(const int);
};

std::ostream&	operator<<(std::ostream&, const Bureaucrat&);
std::ostream&	operator<<(std::ostream&, const Bureaucrat::GradeTooHighException&);
std::ostream&	operator<<(std::ostream&, const Bureaucrat::GradeTooLowException&);

#endif
