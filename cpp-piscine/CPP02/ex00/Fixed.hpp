#ifndef FIXED_H
# define FIXED_H

class	Fixed {
public:
	Fixed();
	~Fixed();

	Fixed(const Fixed&);

	Fixed&	operator=(const Fixed&);

	int		getRawBits(void) const;
	void	setRawBits(int const raw);
	
private:
	static const int	fbits = 8;

	int 				raw;
};

#endif
