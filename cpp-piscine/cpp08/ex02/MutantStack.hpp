#ifndef MUTANTSTACK_H
# define MUTANTSTACK_H

# include <stack>
# include <iterator>

template<class T, class Container = std::deque<T> >
class MutantStack : public std::stack<T, Container> {
public:
	typedef typename Container::iterator iterator;
	typedef typename Container::const_iterator const_iterator;
	typedef typename Container::reverse_iterator reverse_iterator;
	typedef typename Container::const_reverse_iterator const_reverse_iterator;

	MutantStack() : std::stack<T, Container>() {}
	MutantStack(const Container& cont) : std::stack<T, Container>(cont) {}
	MutantStack(const MutantStack& other) : std::stack<T, Container>(other)  {}
	virtual ~MutantStack() {}

	MutantStack&	operator=(const MutantStack& other) {
		if (this == &other)
		return *this;
		std::stack<T, Container>::operator=(other);
		return *this;
	}

	iterator				begin() { return this->std::stack<T, Container>::c.begin(); }
	const_iterator			begin() const { return this->std::stack<T, Container>::c.begin(); }
	iterator				end() { return this->std::stack<T, Container>::c.end(); }
	const_iterator			end() const { return this->std::stack<T, Container>::c.end(); }

	reverse_iterator		rbegin() { return this->std::stack<T, Container>::c.rbegin(); }
	const_reverse_iterator	rbegin() const { return this->std::stack<T, Container>::c.rbegin(); }
	reverse_iterator		rend() { return this->std::stack<T, Container>::c.rend(); }
	const_reverse_iterator	rend() const { return this->std::stack<T, Container>::c.rend(); }

};

#endif
