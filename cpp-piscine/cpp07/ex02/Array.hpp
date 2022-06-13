#ifndef ARRAY_H
# define ARRAY_H

# include <cstddef>

# define SUBSCRIPT_EXC_MSG "Index out of range"

template<typename T>
class Array {
public:
	Array() : tsize(0) {};
	Array(unsigned int n) : tsize(n), tab(new T[n]) {};
	Array(const Array& other) : tsize(other.tsize), tab(other.cloneTab()) {};
	~Array() { delete[] tab; };

	const size_t&	size() const { return tsize; };

	Array&		operator =(const Array& rhs) {
		if (this == &rhs)
			return *this;
		tsize = rhs.tsize;
		delete[] tab;
		tab = rhs.cloneTab();
		return *this;
	}

	T&			operator[](size_t idx) {
	if (idx >= tsize)
		throw std::out_of_range(SUBSCRIPT_EXC_MSG);
	return tab[idx];
	}

	const T&	operator[](size_t idx) const {
		if (idx >= tsize)
			throw std::out_of_range(SUBSCRIPT_EXC_MSG);
		return tab[idx];
	}

private:
	size_t	tsize;
	T*		tab;
	
	T*		cloneTab() const {
		T*	copyTab = new T[tsize];

		for (size_t i = 0; i < tsize; i++) {
			copyTab[i] = tab[i];
		}
		return copyTab;
	}
};

#endif
