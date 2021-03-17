#include <iostream>
#include <vector>
#include <array>
#include <list>
#include "vector.hpp"


int main() {

	int			kek[] = {8, 4,7,4,2,5,7,8,8,9, 10, 12, 13, 14 , 15, 16, 17, 18};
	ft::vector<int> a1(kek, kek + 8);
	std::sort(a1.begin(), a1.end());

	ft::vector<int>::iterator it = a1.begin();
	for (;it != a1.end(); ++it){
		std::cout << *it << std::endl;
	}
	return (0);
}