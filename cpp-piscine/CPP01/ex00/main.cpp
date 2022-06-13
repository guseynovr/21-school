#include "Zombie.hpp"

Zombie*	newZombie(std::string name);
void	randomChump(std::string name);

int	main(void) {
	Zombie *john = newZombie("John");
	Zombie *mary = newZombie("Mary");
	Zombie *mike = newZombie("Mike");

	randomChump("Chump1");
	randomChump("Chump2");
	randomChump("Chump3");

	delete john;
	delete mary;
	delete mike;
}
