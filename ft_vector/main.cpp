#include <iostream>
#include <vector>
#include <array>
#include <list>
#include "vector.hpp"


int main() {

//	int			kek[] = {0, 1,2,3,4,5,6,7,8,9, 10, 12, 13, 14 , 15, 16, 17, 18};
//	std::string	lols[8] = {"1", "2", "3", "4", "5", "6", "7", "8"};
//	std::list<std::string> a(20, "1");
	ft::vector<int>		my1(10, 1);
	std::vector<int>	orig(10, 1);
	my1.reserve(100);
	orig.reserve(100);

	ft::vector<int>::iterator it(my1.begin() + 4);
	std::vector<int>::iterator it_orig(orig.begin() + 4);
	my1.insert(it, 10, 10);
	orig.insert(it_orig, 10, 10);
	std::cout << my1.size() << " " << my1.capacity() <<" " << orig.size() << " " << orig.capacity() << std::endl;
	it = my1.begin();
	it_orig = orig.begin();
	for (;it != my1.end(); ++it, ++it_orig){
		std::cout << *it << " " << *it_orig << std::endl;
	}
	std::cout << my1.size() << " " << my1.capacity() <<" " << orig.size() << " " << orig.capacity() << std::endl;

	return (0);
}