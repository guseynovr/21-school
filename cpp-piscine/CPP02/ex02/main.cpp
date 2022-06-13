#include <iostream>
#include "Fixed.hpp"

int main(void) {
	
	Fixed a;
	Fixed const b( Fixed( 5.05f ) * Fixed( 2 ) );

	std::cout << a << std::endl;
	std::cout << ++a << std::endl;
	std::cout << a << std::endl;
	std::cout << a++ << std::endl;
	std::cout << a << std::endl;

	std::cout << b << std::endl;
	
	std::cout << Fixed::max( a, b ) << std::endl;

	std::cout << "sum: " << Fixed(1.5f) + Fixed(0.5f) << std::endl;
	std::cout << "sum: " << Fixed(1.5f) + Fixed(0.1f) << std::endl;
	std::cout << "dif: " << Fixed(1.5f) - Fixed(0.5f) << std::endl;
	std::cout << "dif: " << Fixed(1.5f) - Fixed(0.1f) << std::endl;
	std::cout << "mul: " << Fixed(1.5f) * Fixed(0.5f) << std::endl;
	std::cout << "mul: " << Fixed(10) * Fixed(0.1f) << std::endl;
	std::cout << "mul: " << Fixed(1.5f) * Fixed(0.5f) << std::endl;
	std::cout << "mul: " << Fixed(1.5f) * Fixed(0.1f) << std::endl;
	std::cout << "div: " << Fixed(1.5f) / Fixed(0.5f) << std::endl;
	std::cout << "div: " << Fixed(1.5f) / Fixed(0.1f) << std::endl;
}
