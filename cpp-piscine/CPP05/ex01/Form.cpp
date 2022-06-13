#include "Form.hpp"

Form::Form() 
:	name("N/A"), 
	signGrade(GR_HIGH),
	execGrade(GR_HIGH),
	isSigned(false) {}

Form::Form(std::string name, int signGrade, int execGrade)
:	name(name),
	signGrade(signGrade),
	execGrade(execGrade),
	isSigned(false) {
	if (this->signGrade < GR_HIGH || execGrade < GR_HIGH)
		throw GradeTooHighException();
	else if (this->signGrade > GR_LOW || execGrade > GR_LOW)
		throw GradeTooLowException();
}

Form::Form(const Form& f)
:	name(f.name),
	signGrade(f.signGrade),
	execGrade(f.execGrade),
	isSigned(f.isSigned) {}

Form::~Form() {}

const std::string&	Form::getName() const {
	return this->name;
}

const int&			Form::getSignGrade() const {
	return this->signGrade;
}

const int&			Form::getExecGrade() const {
	return this->execGrade;
}


const bool&			Form::getIsSigned() const {
	return this->isSigned;
}

void	Form::beSigned(const Bureaucrat& br) {
	if (br.getGrade() <= this->signGrade)
		this->isSigned = true;
	else
		throw GradeTooLowException();
}

Form&	Form::operator=(const Form& other) {
	if (this == &other)
		return *this;
	isSigned = other.isSigned;
	return *this;
}

std::ostream&	operator<<(std::ostream& os, const Form& form) {
	os << "Form " << form.getName()
		<< ". Requires: sign grade " << form.getSignGrade()
		<< ", exec grade " << form.getExecGrade() << ". Status: ";
	if (!form.getIsSigned())
		os << " not ";
	os << "signed.";
	return os;
}

Form::GradeTooHighException::GradeTooHighException () throw()
: descr(std::string("Form: ") + GR_HIGH_DESC) {}

Form::GradeTooHighException::~GradeTooHighException() throw() {}

const char* Form::GradeTooHighException::what() const throw() {
	return this->descr.c_str();
}

Form::GradeTooLowException::GradeTooLowException () throw()
: descr(std::string("Form: ") + GR_LOW_DESC) {}

Form::GradeTooLowException::~GradeTooLowException() throw() {}

const char* Form::GradeTooLowException::what() const throw() {
	return this->descr.c_str();
}
