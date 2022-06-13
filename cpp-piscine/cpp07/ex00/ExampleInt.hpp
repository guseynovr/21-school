#ifndef EXAMPLEINT_H
# define EXAMPLEINT_H

# include <iostream>

class ExampleInt {
public:
	ExampleInt();
	ExampleInt(int);
	ExampleInt(const ExampleInt&);
	~ExampleInt();

	const int&	getValue() const;

	ExampleInt&	operator =(const ExampleInt&);
	bool		operator ==(const ExampleInt&) const;
	bool		operator !=(const ExampleInt&) const;
	bool		operator <(const ExampleInt&) const;
	bool		operator >(const ExampleInt&) const;
	bool		operator <=(const ExampleInt&) const;
	bool		operator >=(const ExampleInt&) const;	

private:
	int	n;
};

std::ostream&	operator <<(std::ostream&, const ExampleInt&);

#endif
