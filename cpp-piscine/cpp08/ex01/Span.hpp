#ifndef SPAN_H
# define SPAN_H

# include <vector>
# include <algorithm>

class Span {
public:
	Span(unsigned int n);
	Span(const Span&);
	~Span();

	void	addNumber(int);

	template<class InputIterator>
	void	addNumber(InputIterator begin, InputIterator end) { 
		if (static_cast<size_t>(std::distance(begin, end))
				> arr.capacity() - arr.size()) {
			throw NoSpaceException();
		}
		arr.insert(arr.end(), begin, end);
	}

	int		shortestSpan();
	int		longestSpan();

	Span&	operator=(const Span&);

	class	NoSpanException : public std::exception {
		virtual const char*	what() const throw();
	};

	class	NoSpaceException : public std::exception {
		virtual const char*	what() const throw();
	};

private:
	std::vector<int>	arr;

	Span();
};

#endif
