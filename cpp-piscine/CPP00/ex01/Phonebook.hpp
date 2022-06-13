#ifndef PHONEBOOK_H
# define PHONEBOOK_H

# include "Contact.hpp"
# include <string>

# define CNRM  "\x1B[0m"
# define CRED  "\x1B[31m"
# define CGRN  "\x1B[32m"
# define CYEL  "\x1B[33m"
# define CBLU  "\x1B[34m"
# define CMAG  "\x1B[35m"
# define CCYN  "\x1B[36m"
# define CWHT  "\x1B[37m"

class Phonebook {
public:

	Phonebook();
	~Phonebook();

	void	open();

private:
	static const int	_max = 8;
	static const int	_field_size = 10;
	int					_idx;
	int					_cnt;
	Contact				_contacts[_max];

	void		_add();
	void		_search();
	void		_input_field(std::string prompt, void (Contact::*set)(std::string));
	std::string	_format(std::string s) const;
	void		_print_all();
	void		_print_id(int id);
};

#endif
