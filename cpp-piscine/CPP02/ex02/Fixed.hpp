#ifndef FIXED_H
# define FIXED_H

# include <iostream>

class	Fixed {

public:

	static Fixed&	min(Fixed&, Fixed&);
	static Fixed&	max(Fixed&, Fixed&);
	static const Fixed&	min(const Fixed&, const Fixed&);
	static const Fixed&	max(const Fixed&, const Fixed&);

	Fixed();
	Fixed(const Fixed&);
	Fixed(const int);
	Fixed(const float);
	~Fixed();

	int		getRawBits(void) const;
	void	setRawBits(const int raw);

	float	toFloat(void) const;
	int		toInt(void) const;

	Fixed&	operator =(const Fixed&);

	bool	operator ==(const Fixed&);
	bool	operator !=(const Fixed&);
	bool	operator <(const Fixed&);
	bool	operator >(const Fixed&);
	bool	operator <=(const Fixed&);
	bool	operator >=(const Fixed&);

	Fixed	operator +(const Fixed&) const;
	Fixed	operator -(const Fixed&) const;
	Fixed	operator *(const Fixed&) const;
	Fixed	operator /(const Fixed&) const;

	Fixed&	operator ++(void);
	Fixed&	operator --(void);
	Fixed	operator ++(int);
	Fixed	operator --(int);
	
private:

	static const int	fbits = 8;

	int 				raw;
};

std::ostream&	operator <<(std::ostream&, const Fixed&);

#endif
