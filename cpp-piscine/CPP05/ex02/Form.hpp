#ifndef FORM_H
# define FORM_H

# include "Bureaucrat.hpp"

class Bureaucrat;

class	Form {
public:
	Form(std::string name, int signGrade, int execGrade);
	Form(const Form&);
	virtual ~Form();

	const std::string&	getName() const;
	const int&			getSignGrade() const;
	const int&			getExecGrade() const;
	const bool&			getIsSigned() const;

	void	beSigned(const Bureaucrat&);
	void	execute(Bureaucrat const & executor) const;

	Form&	operator=(const Form& other);
	
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

	class	FormNotSignedException : public std::exception {
	public:
		FormNotSignedException() throw();
		virtual ~FormNotSignedException() throw();
		virtual const char* what() const throw();
	private:
		const std::string	descr;
	};

protected:
	virtual void	exec() const = 0;
	Form();

private:
	const std::string	name;
	const int			signGrade;
	const int			execGrade;
	bool				isSigned;

};

std::ostream&	operator<<(std::ostream& os, const Form& form);

#endif
