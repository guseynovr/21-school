#include "Karen.hpp"
#include <iostream>

Karen::Karen() {
	this->_level_names[0] = "DEBUG";
	this->_level_names[1] = "INFO";
	this->_level_names[2] = "WARNING";
	this->_level_names[3] = "ERROR";
}

int	Karen::_get_level(std::string level) {
	for (int i = 0; i < 4; i++)
		if (level == _level_names[i])
			return i;
	return -1;
}	

void	Karen::complain(std::string level) {
	switch(_get_level(level)) {
	case DEBUG:
		debug();
	case INFO:
		info();
	case WARNING:
		warning();
	case ERROR:
		error();
		break;
	default:
		std::cout << "[ Probably complaining about insignificant problems ]"
			<< std::endl;
	}
}

void	Karen::debug() {
	std::cout << "[ DEBUG ]\n"
		"I love to get extra bacon for my "
		"7XL-double-cheese-triple-pickle-special-ketchup burger."
		"I just love it!\n" << std::endl;
}

void	Karen::info() {
	std::cout << "[ INFO ]\n"
		"I cannot believe adding extra bacon cost more money. "
		"You don’t put enough! If you did I would not have to ask for it!\n"
		<< std::endl;
}

void	Karen::warning() {
	std::cout << "[ WARNING ]\n"
		"I think I deserve to have some extra bacon for free."
		" I’ve been coming here for years and you just started working here "
		"last month.\n" << std::endl;
}

void	Karen::error() {
	std::cout << "[ ERROR ]\n"
		"This is unacceptable, I want to speak to the manager now." << std::endl;
}

