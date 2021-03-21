#include <iostream>
#include "ft_list.hpp"
#include <list>

int main() {
	std::list<int> orig_a0(10, 1);
	std::cout << orig_a0.max_size() << std::endl;
	std::cout << sizeof(orig_a0) << std::endl;
	std::list<std::list<int> > orig_a(10, orig_a0);
	std::cout << orig_a.max_size() << std::endl;

	ft::list<std::string> a(10, "f");
	std::cout << a.max_size() << std::endl;
	return 0;
}
