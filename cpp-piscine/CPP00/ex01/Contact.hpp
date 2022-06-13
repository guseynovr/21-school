#ifndef CONTACT_H
# define CONTACT_H

# include <string>

class Contact {
public:
	Contact();
	~Contact();

	std::string	get_firstname() const;
	std::string	get_lastname() const;
	std::string	get_nickname() const;
	std::string	get_phonenumber() const;
	std::string	get_darkestsecret() const;

	void		set_firstname(std::string first);
	void		set_lastname(std::string last);
	void		set_nickname(std::string nick);
	void		set_phonenumber(std::string phone);
	void		set_darkestsecret(std::string secret);

private:
	std::string	_first_name;
	std::string	_last_name;
	std::string	_nickname;
	std::string	_phone_number;
	std::string	_darkest_secret;
};

#endif
