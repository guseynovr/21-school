#include <ctime>
#include <iomanip>
#include <iostream>
#include "Account.hpp"

int	Account::getNbAccounts( void ) {
	return Account::_nbAccounts;
}

int	Account::getTotalAmount( void ) {
	return Account::_totalAmount;
}

int	Account::getNbDeposits( void ) {
	return Account::_totalNbDeposits;
}
int	Account::getNbWithdrawals( void ) {
	return Account::_totalNbWithdrawals;
}

void	Account::displayAccountsInfos( void ) {
	Account::_displayTimestamp();
	std::cout << "accounts:" << _nbAccounts << ";total:" << _totalAmount
		<< ";deposits:" << _totalNbDeposits
		<< ";withdrawals:" << _totalNbWithdrawals << std::endl;
}

Account::Account( int initial_deposit ) {
	this->_accountIndex = Account::_nbAccounts++;
	Account::_totalAmount += initial_deposit;
	this->_nbDeposits = 0;
	this->_nbWithdrawals = 0;
	this->_amount = initial_deposit;
	Account::_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";amount:" << _amount
		<< ";created" << std::endl;
}

Account::~Account( void ) {
	Account::_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";amount:" << _amount
		<< ";closed" << std::endl;
}

void	Account::makeDeposit( int deposit ) {
	Account::_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";p_amount:"
		<< _amount << ";deposit:" << deposit;
	this->_amount += deposit;
	this->_nbDeposits++;
	Account::_totalAmount += deposit;
	Account::_totalNbDeposits++;
	std::cout << ";amount:" << _amount << ";nb_deposits:" << _nbDeposits
		<< std::endl;
}

bool	Account::makeWithdrawal( int withdrawal ) {
	Account::_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";p_amount:" << _amount
		<< ";withdrawal:";
	if (this->_amount >= withdrawal) {
		this->_amount -= withdrawal;
		this->_nbWithdrawals++;
		Account::_totalNbWithdrawals++;
		Account::_totalAmount -= withdrawal;
		std::cout << withdrawal << ";amount:" << _amount
			<< ";nb_withdrawals:" << _nbWithdrawals << std::endl;
		return true;
	} else {
		std::cout << "refused" << std::endl;
		return false;
	}
}

int		Account::checkAmount( void ) const {
	return this->_amount;
}
void	Account::displayStatus( void ) const {
	Account::_displayTimestamp();
	std::cout << "index:" << _accountIndex << ";amount:" << _amount
		<< ";deposits:" << _nbDeposits << ";withdrawals:" << _nbWithdrawals
		<< std::endl;
}

void	Account::_displayTimestamp( void ) {
	time_t		raw_time;
	struct tm	tm;
	
	time(&raw_time);
	tm = *localtime(&raw_time);
	std::cout << "[" << std::setfill('0') 
		<< tm.tm_year + 1900
		<< std::setw(2) << tm.tm_mon + 1
		<< std::setw(2) << tm.tm_mday << "_"
		<< std::setw(2) << tm.tm_hour
		<< std::setw(2) << tm.tm_min + tm.tm_sec / 60
		<< std::setw(2) << tm.tm_sec % 60 << "]";
	// std::cout << "[19920104_091532] ";
};

int	Account::_nbAccounts;
int	Account::_totalAmount;
int	Account::_totalNbDeposits;
int	Account::_totalNbWithdrawals;
