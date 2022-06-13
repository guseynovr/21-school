#include <fstream>
#include <iostream>

void	mreplace(std::string& s, std::string oldv, std::string newv) {
	size_t	start;

	start = s.find(oldv);
	while (start != std::string::npos) {
		s = s.substr(0, start) + newv + s.substr(start + oldv.size());
		start = s.find(oldv);
	}
}

int main(int argc, char **argv) {
	if (argc != 4) {
		std::cout << "Usage: ./replace filename oldstring newstring"
			<< std::endl;
		return 1;
	}
	if (std::string(argv[2]).size() == 0 || std::string(argv[3]).size() == 0) {
		std::cout << "Strings must not be empty" << std::endl;
		return 1;
	}

	std::ifstream	ifile;
	std::ofstream	ofile;
	std::string		ifilename = std::string(argv[1]);
	std::string		ofilename = std::string(argv[1]) + ".replace";

	ifile.open(ifilename);
	if (!ifile.is_open()) {
		std::cout << "Can't open file for reading: " << ifilename << std::endl;
		return 1;
	}
	ofile.open(ofilename);
	if (!ofile.is_open()) {
		std::cout << "Can't open file for writing: " << ofilename
			<< std::endl;
		ifile.close();
		return 1;
	}

	std::string	newstr;

	while (getline(ifile, newstr)) {
		mreplace(newstr, std::string(argv[2]), std::string(argv[3]));
		ofile << newstr << std::endl;
		if (!ofile.good()) {
			std::cout << "An error occurred while writing to file: "
				<< ofilename << std::endl;
			ifile.close();
			ofile.close();
			return 1;
		}
	}
	if (!ifile.eof()) {
		std::cout << "An error occurred while reading file: " << ifilename
			<< std::endl;
		ifile.close();
		ofile.close();
		return 1;
	}
	ifile.close();
	ofile.close();
	return 0;
}
