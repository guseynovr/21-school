#include <iostream>
#include <cstring>
#include <cctype>

int main(int argc, char **argv) 
{
	if (argc < 2) {
		std::cout << "* LOUD AND UNBEARABLE FEEDBACK NOISE *" << std::endl;
		return (1);
	}

	std::string	s;
	int			len;

	for (int i = 1; i < argc; i++) {
		s = std::string(argv[i]);
		len = s.size();
		for (int j = 0; j < len; j++)
			std::cout << static_cast<char>(std::toupper(s[j]));
	}
	std::cout << std::endl;
}
