#include <iostream>
#include <vector>
#include <array>
#include "vector.hpp"




int main() {

	int			kek[] = {0, 1,2,3,4,5,6,7,8,9, 10, 12, 13, 14 , 15, 16, 17, 18};
	std::vector<int>	orig(10, 4);
//	orig.push_back(10);
	ft::vector<int>		my(kek, kek + 4);
	ft::vector<int>		my1(10, 1);
	orig.assign(kek, kek + 5);
	std::cout << orig.capacity() << std::endl;
	std::cout << orig[9] << std::endl;
	my1.assign(kek, kek + 10);
	return (0);
}