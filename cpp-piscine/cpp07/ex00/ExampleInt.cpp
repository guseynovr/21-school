#include "ExampleInt.hpp"

ExampleInt::ExampleInt() : n(0) {}

ExampleInt::ExampleInt(int num) : n(num) {}

ExampleInt::ExampleInt(const ExampleInt& other) : n(other.n) {}

ExampleInt::~ExampleInt() {}

const int&	ExampleInt::getValue() const {
	return n;
}

ExampleInt&	ExampleInt::operator =(const ExampleInt& rhs) {
	if (this == &rhs)
		return *this;
	n = rhs.n;
	return *this;
}

bool		ExampleInt::operator ==(const ExampleInt& rhs) const {
	return n == rhs.n;
}

bool		ExampleInt::operator !=(const ExampleInt& rhs) const {
	return n != rhs.n;
}

bool		ExampleInt::operator <(const ExampleInt& rhs) const {
	return n < rhs.n;
}

bool		ExampleInt::operator >(const ExampleInt& rhs) const {
	return n > rhs.n;
}

bool		ExampleInt::operator <=(const ExampleInt& rhs) const {
	return n <= rhs.n;
}

bool		ExampleInt::operator >=(const ExampleInt& rhs) const {
	return n >= rhs.n;
}

std::ostream&	operator <<(std::ostream& os, const ExampleInt& rhs) {
	os << rhs.getValue();
	return os;
}
