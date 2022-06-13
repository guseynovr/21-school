#include "iter.hpp"
#include "ExampleInt.hpp"
#include <string>
#include <iostream>

template<typename T>
void	print(T obj) {
	std::cout << obj << "\n";
}

int	main() {
	std::string strs[5] = {"apple", "orange", "grape", "banana", "mango"};

	iter(strs, 5, print);

	ExampleInt	nums[5] = { 0, -222, 3, 4, 5};

	iter(nums, 5, print);
}
