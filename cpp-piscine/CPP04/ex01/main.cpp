#include "Dog.hpp"
#include "Cat.hpp"
#include <iostream>

int main() {
	const Animal* animals[10];

	for (int i = 0; i < 5; i++)
		animals[i] = new Cat();

	for (int i = 5; i < 10; i++)
		animals[i] = new Dog();

	for (int i = 0; i < 10; i++)
		delete animals[i];

	const Cat* cat = new Cat();
	const Cat* catCopy = new Cat(*cat);

	std::cout << "cat brain addr: " << cat->getBrain() << std::endl;
	std::cout << "catCopy brain addr: " << catCopy->getBrain() << std::endl;

	Dog	dog;
	{
		Dog	tmp = dog;
	}

	std::cout << "dog brain : " << dog.getBrain() << std::endl;
}
