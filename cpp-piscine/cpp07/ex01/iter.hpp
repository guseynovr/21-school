#ifndef ITER_H
# define ITER_H

# include <cstddef>

template<typename T>
void	iter(T* arr, size_t size, void (*f)(const T& obj)) {
	for (size_t i = 0; i < size; i++) {
		f(arr[i]);
	}
}

#endif
