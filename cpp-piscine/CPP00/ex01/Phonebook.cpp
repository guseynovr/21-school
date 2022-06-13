#include "Phonebook.hpp"
#include <iostream>
#include <iomanip>

Phonebook::Phonebook() {
	this->_idx = -1;
	this->_cnt = 0;
}

Phonebook::~Phonebook() {}

void	out_closed() {
	std::cout << CRED << "\nStandart input stream is closed" << CNRM 
			<< std::endl;
		std::exit(1);
}

void	Phonebook::_input_field(std::string prompt,
void (Contact::*set)(std::string)) {
	std::string	input = "";

	std::cout << prompt << ": ";
	std::getline(std::cin, input);
	if (std::cin.eof())
		out_closed();
	(_contacts[this->_idx].*set)(input);
}

void	Phonebook::_add() {
	Contact		contact;
	std::string	input;

	if (_cnt < _max)
		_cnt++;
	_idx++;
	if (this->_idx >= this->_max)
		_idx = 0;
	std::cout << CYEL << "Input new contact info" << CNRM << std::endl;
	_input_field("First name", &Contact::set_firstname);
	_input_field("Last name", &Contact::set_lastname);
	_input_field("Nick name", &Contact::set_nickname);
	_input_field("Phone number", &Contact::set_phonenumber);
	_input_field("Darkest secret", &Contact::set_darkestsecret);
	std::cout << CGRN << "Contact added" << CNRM << std::endl;
}

std::string	Phonebook::_format(std::string s) const {
	if (s.size() > _field_size)
		return s.substr(0, _field_size - 1) + '.';
	return s;
}

bool	is_num(std::string s) {
	if (s.size() == 0)
		return false;
	for (int i = 0; s[i]; i++)
		if (!std::isdigit(s[i]))
			return false;
	return true;
}

void	to_uppercase(std::string & s) {
	for (int i = 0; s[i]; i++)
		s[i] = std::toupper(s[i]);
}

void	Phonebook::_print_all() {		
	std::cout << "┌──────────┬──────────┬──────────┬──────────┐\n";
	std::cout << "│   Index  │First name│ Last name│ Nickname │\n";
	for (int i = 0; i < this->_cnt; i++) {
		std::cout << "├──────────┼──────────┼──────────┼──────────┤\n"
			<< "│" << std::string(_field_size - 1, ' ') << i << "│"
			<< std::setw(_field_size) << _format(this->_contacts[i].get_firstname()) << "│"
			<< std::setw(_field_size) << _format(this->_contacts[i].get_lastname()) << "│"
			<< std::setw(_field_size) << _format(this->_contacts[i].get_nickname()) << "│"
			<< std::endl;
	}
	std::cout << "└──────────┴──────────┴──────────┴──────────┘" << std::endl;
}

void	Phonebook::_print_id(int id) {
	std::cout << "First name: " << this->_contacts[id].get_firstname() << "\n"
		<< "Last_name: " << this->_contacts[id].get_lastname() << "\n"
		<< "Nickname: " << this->_contacts[id].get_nickname() << "\n"
		<< "Phone number: " << this->_contacts[id].get_phonenumber() << "\n"
		<< "Darkest secret: " << this->_contacts[id].get_darkestsecret() 
		<< std::endl;
}

void	Phonebook::_search() {
	std::string	s;
	int			id = -1;

	if (_cnt == 0) {
		std::cout << CRED << "Phonebook is empty" << CNRM << std::endl;
		return;
	}
	_print_all();
	std::cout << CYEL << "Choose entry id: " << CNRM;
	std::getline(std::cin, s);
	if (std::cin.eof())
		out_closed();
	if (is_num(s))
		id = std::stoi(s);
	else {
		std::cout << CRED << "Invalid entry id" << CNRM << std::endl;
		return;
	}
	if (id < 0 || id >= _cnt) {
		std::cout << CRED << "No such entry" << CNRM << std::endl;
		return;
	}
	_print_id(id);
}

void	Phonebook::open() {
	std::string	s = "";

	std::cout << CGRN << "Phonebook opened" << CNRM << std::endl;
	while (s != "EXIT") {
		if (s == "ADD") {
			this->_add();
		} else if (s == "SEARCH") {
			this->_search();
		} else {
			std::cout << CBLU << "Available commands: ADD, SEARCH, EXIT" 
				<< CNRM << std::endl;
		}
		std::cout << CYEL << "Input a command: " << CNRM;
		std::getline(std::cin, s);
		if (std::cin.eof())
			out_closed();
		to_uppercase(s);
	}
	std::exit(0);
}
