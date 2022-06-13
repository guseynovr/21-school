#include <iostream>
#include <MutantStack.hpp>
#include <vector>

int	main() {
	MutantStack<int> mstack;

	mstack.push(5);
	mstack.push(17);

	std::cout << mstack.top() << std::endl;

	mstack.pop();

	std::cout << mstack.size() << std::endl;

	mstack.push(3);
	mstack.push(5);
	mstack.push(737);
	//[...]
	mstack.push(0);

	MutantStack<int>::iterator it = mstack.begin();
	MutantStack<int>::iterator ite = mstack.end();

	++it;
	--it;
	while (it != ite) {
		std::cout << *it << std::endl;
		++it;
	}

	MutantStack<int>::reverse_iterator itr = mstack.rbegin();
	MutantStack<int>::reverse_iterator itre = mstack.rend();

	while (itr != itre) {
		std::cout << *itr << std::endl;
		++itr;
	}

	std::stack<int>		s(mstack);
	std::vector<int>	v(0);
	std::deque<int>		deq;

	deq.push_front(1);
	deq.push_front(2);
	deq.push_front(4);
	deq.push_front(40);

	MutantStack<int> mstack2(deq);
	MutantStack<int, std::vector<int> > mstack3(v);

	mstack3.begin();
	
	return 0;
}
