#ifndef FIXED_H
# define FIXED_H

# include <iostream>

class	Fixed {
public:
	Fixed();
	Fixed(const Fixed&);
	Fixed(const int);
	Fixed(const float);
	~Fixed();

	int			getRawBits(void) const;
	void		setRawBits(const int raw);

	float		toFloat(void) const;
	int			toInt(void) const;

	Fixed&		operator=(const Fixed&);
	
private:
	static const int	fbits = 8;

	int 				raw;
};

std::ostream&	operator<<(std::ostream&, const Fixed&);

#endif
