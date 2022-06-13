#include "Span.hpp"
#include <cmath>
#include <limits>

Span::Span(unsigned int n)
:	arr(std::vector<int>(n)) {
	arr.resize(0);
}

Span::Span(const Span& other)
:	arr(std::vector<int>(other.arr)) {}

Span::~Span() {}

void	Span::addNumber(int num) {
	if (arr.capacity() > arr.size())
		arr.push_back(num);
	else
		throw NoSpaceException();
}

int		Span::shortestSpan() {
	if (arr.size() < 2)
		throw NoSpanException();
	int	min = std::numeric_limits<int>::max();
	std::sort(arr.begin(), arr.end());
	for (std::vector<int>::iterator it = arr.begin(); it != arr.end() - 1; ++it) {
		if (abs(*it - *(it + 1)) < min)
			min = abs(*it - *(it + 1));
	}
	return min;
}

int		Span::longestSpan() {
	if (arr.size() < 2)
		throw NoSpanException();
	std::vector<int>::iterator	max = std::max_element(arr.begin(), arr.end());
	std::vector<int>::iterator	min = std::min_element(arr.begin(), arr.end());
	return *max - *min;
}

Span&	Span::operator=(const Span& other) {
	if (this == &other)
		return *this;
	arr = other.arr;
	return *this;
}

const char*	Span::NoSpanException::what() const throw() {
	return "No span";
}

const char*	Span::NoSpaceException::what() const throw() {
	return "Not enough space";
}

