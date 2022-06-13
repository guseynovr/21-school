#include <iostream>
#include <iomanip>
#include <string>
#include <limits>

# define WIDTH 8

void	print_char(double value) {
	char	ch;

	std::cout << std::setw(WIDTH) << "char: ";
	try {
		if (value < std::numeric_limits<char>::min()
			|| value > std::numeric_limits<char>::max()
			|| value != value)
			throw std::out_of_range("char");
		ch = static_cast<char>(value);
		if (std::isprint(ch))
			std::cout << "'" << ch << "'" << std::endl;
		else 
			std::cout << "non printable" << std::endl;
	} catch (std::exception& e) {
		std::cout << "impossible" << std::endl;
	}
}

void	print_int(double value) {
	int	i;

	std::cout << std::setw(WIDTH) << "int: ";
	try {
		if (value < std::numeric_limits<int>::min()
			|| value > std::numeric_limits<int>::max()
			|| value != value)
			throw std::out_of_range("int");
		i = static_cast<int>(value);
		std::cout << i << std::endl;
	} catch (std::exception& e) {
		std::cout << "impossible" << std::endl;
	}
}

void	print_float(double value) {
	float	f;

	std::cout << std::setw(WIDTH) << "float: ";
	try {
		f = static_cast<float>(value);
		std::cout.setf(std::ios::showpoint);
		std::cout << f << "f" << std::endl;
	} catch (std::exception& e) {
		std::cout << "impossible" << std::endl;
	}
}

void	 print_double(double value) {
	double	d;
	
	std::cout << std::setw(WIDTH) << "double: ";
	try {
		d = static_cast<double>(value);
		std::cout << d << std::endl;
	} catch (std::exception& e) {
		std::cout << "impossible" << std::endl;
	}
}

int	main(int argc, char **argv) {
	if (argc != 2)
		return 1;

	std::string	s(argv[1]);
	double		value;

	try {
		value = stod(s);
	} catch (std::exception& e) {
		std::cout << "Invalid intput\n";
		return 1;
	}

	print_char(value);
	print_int(value);
	print_float(value);
	print_double(value);
}
