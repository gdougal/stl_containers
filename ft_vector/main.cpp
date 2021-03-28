#include "vector.hpp"
#include <iostream>

int main() {
	ft::vector<int> a(10, 10);
	uint64_t a2 = 10;
	uint64_t a3 = 11;
	ft::vector<uint64_t>	a1(a2, a3);
	return 0;
}
