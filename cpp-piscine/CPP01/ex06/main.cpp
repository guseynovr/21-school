#include "Karen.hpp"
#include <iostream>

int main(int argc, char **argv) {
	if (argc != 2)
		return 1;

	Karen karen;

	karen.complain(std::string(argv[1]));
}
