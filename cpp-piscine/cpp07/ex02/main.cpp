#include <iostream>
#include <Array.hpp>
#include <sstream>

#define MAX_VAL 750
int main(int, char**)
{
    Array<int> numbers(MAX_VAL);
    int* mirror = new int[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
        numbers[i] = value;
        mirror[i] = value;
    }
    //SCOPE
    {
        Array<int> tmp = numbers;
        Array<int> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    try
    {
        numbers[-2] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
        numbers[MAX_VAL] = 0;
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        numbers[i] = rand();
    }
    delete [] mirror;//
    return 0;

	/* Array<std::string> numbers(MAX_VAL);
    std::string* mirror = new std::string[MAX_VAL];
    srand(time(NULL));
    for (int i = 0; i < MAX_VAL; i++)
    {
        const int value = rand();
		std::ostringstream	temp;
		temp << value;
        numbers[i] = std::string(temp.str());
        mirror[i] = std::string(temp.str());
    }
    //SCOPE
    {
        Array<std::string> tmp = numbers;
        Array<std::string> test(tmp);
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
        if (mirror[i] != numbers[i])
        {
            std::cerr << "didn't save the same value!!" << std::endl;
            return 1;
        }
    }
    try
    {
		std::ostringstream	temp;
		temp << 0;
        numbers[-2] = std::string(temp.str());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }
    try
    {
		std::ostringstream	temp;
		temp << 0;
        numbers[MAX_VAL] = std::string(temp.str());
    }
    catch(const std::exception& e)
    {
        std::cerr << e.what() << '\n';
    }

    for (int i = 0; i < MAX_VAL; i++)
    {
		std::ostringstream	temp;
		temp << rand();
        numbers[i] = temp.str();
    }
    delete [] mirror;//
    return 0; */

/* 	Array<int>	arr;

	std::cout << arr.size() << std::endl;
	try {
		int	temp = arr[0];
		std::cout << temp << std::endl;
	} catch (std::exception& e) {
		std::cerr << e.what() << '\n';
	} */
}
