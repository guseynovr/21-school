#include "Contact.hpp"

Contact::Contact() {};

Contact::~Contact() {};

std::string	Contact::get_firstname() const {
	return this->_first_name;
}

std::string	Contact::get_lastname() const {
	return this->_last_name;
}

std::string	Contact::get_nickname() const {
	return this->_nickname;
}

std::string	Contact::get_phonenumber() const {
	return this->_phone_number;
}

std::string	Contact::get_darkestsecret() const {
	return this->_darkest_secret;
}

void	Contact::set_firstname(std::string first) {
	this->_first_name = first;
}

void	Contact::set_lastname(std::string last) {
	this->_last_name = last;
}

void	Contact::set_nickname(std::string nick) {
	this->_nickname = nick;
}

void	Contact::set_phonenumber(std::string phone) {
	this->_phone_number = phone;
}

void	Contact::set_darkestsecret(std::string secret) {
	this->_darkest_secret = secret;
}
