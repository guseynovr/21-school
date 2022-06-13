#include "Karen.hpp"
#include <iostream>

Karen::Karen() {
	this->f[0] = &Karen::debug;
	this->f[1] = &Karen::info;
	this->f[2] = &Karen::warning;
	this->f[3] = &Karen::error;

	this->_level_names[0] = "DEBUG";
	this->_level_names[1] = "INFO";
	this->_level_names[2] = "WARNING";
	this->_level_names[3] = "ERROR";
}

int	Karen::get_level(std::string level) {
	for (int i = 0; i < 4; i++)
		if (level == _level_names[i])
			return i;
	return -1;
}	

void	Karen::complain(std::string level) {
	int l = get_level(level);

	if (l == -1)
		std::cout << "No such level" << std::endl;
	else
		(this->*f[l])();
}

void	Karen::debug() {
	std::cout << "DEBUG: I love to get extra bacon for my "
		"7XL-double-cheese-triple-pickle-special-ketchup burger."
		"I just love it!" << std::endl;
}

void	Karen::info() {
	std::cout << "INFO: I cannot believe adding extra bacon cost more money. "
		"You don’t put enough! If you did I would not have to ask for it!"
		<< std::endl;
}

void	Karen::warning() {
	std::cout << "WARNING: I think I deserve to have some extra bacon for free."
		" I’ve been coming here for years and you just started working here "
		"last month." << std::endl;
}

void	Karen::error() {
	std::cout << "ERROR: This is unacceptable, I want to speak to the manager "
		"now." << std::endl;
}

