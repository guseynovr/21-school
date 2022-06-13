#include <easyfind.hpp>
#include <iostream>
#include <vector>
#include <list>

int	main() {
	int	arr[] = {532, 453, 82935, 7801};
	int	arrSize = sizeof(arr) / sizeof(int);

	std::vector<int> vect(arr, arr + arrSize);
	try {
		std::cout << "easyfind vector(532): " << *easyfind(vect, 532) << "\n";
	} catch (std::exception& e) {
		std::cout << "Not found\n";
	}
	try {
		std::cout << "easyfind vector(111): " << *easyfind(vect, 111) << "\n";
	} catch (std::exception& e) {
		std::cout << "Not found\n";
	}

	std::list<int> list(std::begin(arr), std::end(arr));
	try {
		std::cout << "easyfind list(7801): " << *easyfind(vect, 7801) << "\n";
	} catch (std::exception& e) {
		std::cout << "Not found\n";
	}
	try {
		std::cout << "easyfind list(400): " << *easyfind(vect, 400) << "\n";
	} catch (std::exception& e) {
		std::cout << "Not found\n";
	}
}
