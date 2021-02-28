#include <iostream>
#include <list>
#include "ft_list.hpp"


struct s_node {
	int lol;
	struct s_node *next;
};


int main() {
	std::list<struct s_node, std::allocator<struct s_node> > kek;
	std::cout << "Hello, World!" << std::endl;
	ft::list<struct s_node, std::allocator<struct s_node> > kek1;
	return 0;
}
