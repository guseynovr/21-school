#ifndef BUREAUCRAT_H
# define BUREAUCRAT_H

# define GR_HIGH	1
# define GR_LOW		150

# define GR_HIGH_DESC	"Grade too high exception"
# define GR_LOW_DESC	"Grade too low exception"

# include <string>
# include <iostream>

class Bureaucrat {
public:
	Bureaucrat(const std::string name, const int grade);
	Bureaucrat(const Bureaucrat& other);
	~Bureaucrat();

	const std::string&	getName() const;
	const int&			getGrade() const;

	void	upgrade();
	void	downgrade();

	Bureaucrat& operator=(const Bureaucrat& other);

	class GradeTooHighException : public std::exception {
	public:
		GradeTooHighException() throw();
		virtual ~GradeTooHighException() throw();
		virtual const char* what() const throw();

	private:
		const std::string	descr;
	};

	class GradeTooLowException : public std::exception {
	public:
		GradeTooLowException() throw();
		virtual ~GradeTooLowException() throw();
		virtual const char* what() const throw();
	private:
		const std::string	descr;
	};

private:
	Bureaucrat(); 

	void	setGrade(const int);

	const std::string	name;
	int					grade;
};

std::ostream&	operator<<(std::ostream&, const Bureaucrat&);
std::ostream&	operator<<(std::ostream&, const Bureaucrat::GradeTooHighException&);
std::ostream&	operator<<(std::ostream&, const Bureaucrat::GradeTooLowException&);


#endif
