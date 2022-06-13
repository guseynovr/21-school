#ifndef EASYFIND_H
# define EASYFIND_H

# include <iterator>
# include <algorithm>

template <typename T>
typename T::iterator	easyfind(T x, int cmp) {
	typename T::iterator it = std::find(x.begin(), x.end(), cmp);
	if (it == x.end())
		throw std::exception();
	return it;
}

#endif
