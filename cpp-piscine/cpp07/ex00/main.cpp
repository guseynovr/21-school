#include "whatever.hpp"
#include "ExampleInt.hpp"
#include <iostream>
#include <string>

int	main() {
	std::string	s1("hello");
	std::string	s2("hello");
	std::string	s3("HELLO");

	std::cout << "\ns1 = " << s1 << ", s2 = " << s2 << ", s3 = " << s3 << "\n";
	swap(s2, s3);
	std::cout << "swap(s2, s3); s2 = " << s2 << ", s3 = " << s3 << "\n";
	std::cout << "min(s1, s2) = " << ::min(s1, s2) << "\n";
	std::cout << "max(s1, s2) = " << ::max(s1, s2) << std::endl;

	float	f1 = 0.f;
	float	f2 = -9.2f;
	float	f3 = 0.012f;

	std::cout << "\nf1 = " << f1 << ", f2 = " << f2 << ", f3 = " << f3 << "\n";
	swap(f2, f3);
	std::cout << "swap(f2, f3); f2 = " << f2 << ", f3 = " << f3 << "\n";
	std::cout << "min(f1, f2) = " << ::min(f1, f2) << "\n";
	std::cout << "max(f1, f2) = " << ::max(f1, f2) << std::endl;

	ExampleInt	ei1(1);
	ExampleInt	ei2(2);
	ExampleInt	ei3(3);

	std::cout << "\nei1 = " << ei1 << ", ei2 = " << ei2 << ", ei3 = " << ei3
		<< "\n";
	swap(ei2, ei3);
	std::cout << "swap(ei2, ei3); ei2 = " << ei2 << ", ei3 = " << ei3 << "\n";
	std::cout << "min(ei1, ei2) = " << ::min(ei1, ei2) << "\n";
	std::cout << "max(ei1, ei2) = " << ::max(ei1, ei2) << std::endl;
}
