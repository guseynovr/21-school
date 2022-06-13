#include "Bureaucrat.hpp"

Bureaucrat::Bureaucrat() {}

Bureaucrat::Bureaucrat(const std::string name, const int grade) : name(name) {
	setGrade(grade);
}

Bureaucrat::Bureaucrat(const Bureaucrat& other)
: name(other.name), grade(other.getGrade()) {}

Bureaucrat::~Bureaucrat() {}

const std::string&	Bureaucrat::getName() const {
	return this->name;
}

const int&			Bureaucrat::getGrade() const {
	return this->grade;
}

void	Bureaucrat::setGrade(const int value) {
	if (value >= GR_HIGH && value <= GR_LOW)
		this->grade = value;
	else if (value < GR_HIGH)
		throw GradeTooHighException();
	else
		throw GradeTooLowException();
}

void	Bureaucrat::upgrade() {
	setGrade(this->grade - 1);
}

void	Bureaucrat::downgrade() {
	setGrade(this->grade + 1);
}

void	Bureaucrat::signForm(Form& form) const {
	try {
		form.beSigned(*this);
		std::cout << *this << " signs form <" << form << ">" << std::endl;
	} catch (std::exception& e) {
		std::cout << *this << " cannot sign form <" << form << "> because "
			<< e.what() << std::endl;
	}
}

Bureaucrat&		Bureaucrat::operator=(const Bureaucrat& other) {
	if (this == &other)
		return *this;
	this->grade = other.grade;
	return *this;
}
std::ostream&	operator<<(std::ostream& os, const Bureaucrat& bureaucrat) {
	os << bureaucrat.getName() << ", bureaucrat grade "
		<< bureaucrat.getGrade();
	return os;
}

Bureaucrat::GradeTooHighException::GradeTooHighException () throw()
: descr(std::string("Bureaucrat: ") + GR_HIGH_DESC) {}

Bureaucrat::GradeTooHighException::~GradeTooHighException() throw() {}

const char* Bureaucrat::GradeTooHighException::what() const throw() {
	return this->descr.c_str();
}

Bureaucrat::GradeTooLowException::GradeTooLowException () throw()
: descr(std::string("Bureaucrat: ") + GR_LOW_DESC) {}

Bureaucrat::GradeTooLowException::~GradeTooLowException() throw() {}

const char* Bureaucrat::GradeTooLowException::what() const throw() {
	return this->descr.c_str();
}
