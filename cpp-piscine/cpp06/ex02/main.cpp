#include <iostream>
#include <cstdlib>

class Base {
public:
	virtual ~Base() {};
};

class A : public Base {};

class B : public Base {};

class C : public Base {};

Base * generate(void) {
	std::srand(std::time(nullptr));
	int	id = std::rand() % 3;

	switch (id) {
	case 0:
		std::cout << "An instance of class A created\n";
		return new A();
	case 1:
		std::cout << "An instance of class B created\n";
		return new B();
	case 2:
		std::cout << "An instance of class C created\n";
		return new C();
	default:
		std::cout << "An instance of class Base created\n";
		return new Base();
	}
}

void identify(Base* p) {
	A*	a = dynamic_cast<A *>(p);
	if (a) {
		std::cout << "A" << std::endl;
		return;
	}

	B*	b = dynamic_cast<B *>(p);
	if (b) {
		std::cout << "B" << std::endl;
		return;
	}

	C*	c = dynamic_cast<C *>(p);
	if (c) {
		std::cout << "C" << std::endl;
		return;
	}

	std::cout << "Base" << std::endl;
}

void identify(Base& p) {
	try {
		A&	a = dynamic_cast<A&>(p);
		(void) a;
		std::cout << "A" << std::endl;
		return;
	} catch (std::exception& e) {}

	try {
		B&	b = dynamic_cast<B&>(p);
		(void) b;
		std::cout << "B" << std::endl;
		return;
	} catch (std::exception& e) {}

	try {
		C&	c = dynamic_cast<C&>(p);
		(void) c;
		std::cout << "C" << std::endl;
		return;
	} catch (std::exception& e) {}

	std::cout << "Base" << std::endl;
}

int	main() {
	Base*	p = generate();
	// Base*	p = new Base();

	identify(p);
	std::cout << "Reference\n";
	identify(*p);
	delete p;
}
