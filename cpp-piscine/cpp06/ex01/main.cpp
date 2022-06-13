#include <iostream>
#include <string>

typedef struct s_data {
	std::string	s;
} Data;

uintptr_t	serialize(Data* ptr) {
	return reinterpret_cast<uintptr_t>(ptr);
}

Data*		deserialize(uintptr_t raw) {
	return reinterpret_cast<Data*>(raw);
}

int	main() {
	Data		data;
	uintptr_t	raw;
	Data*		ptr;

	data.s = "some data";
	std::cout << data.s << std::endl;
	raw = serialize(&data);
	ptr = deserialize(raw);
	std::cout << data.s << std::endl;
}
