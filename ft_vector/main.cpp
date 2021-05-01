#include "vector.hpp"
#include <iostream>

int main() {
	std::string s[10] = {"1", "2", "2", "2", "2", "2", "2", "2"};
	ft::vector<std::string> a1(s, s + 5);
	ft::vector<std::string>::const_iterator it = a1.begin();
	uint64_t a2 = 10;
	uint64_t a3 = 11;

//	ft::vector<uint64_t>	a1(a2, a3);
	return 0;
}
