#include <iostream>
#include <vector>
#include <array>
#include <list>
#include "vector.hpp"


int main() {

//	int			kek[] = {0, 1,2,3,4,5,6,7,8,9, 10, 12, 13, 14 , 15, 16, 17, 18};
	std::string	lols[8] = {"1", "2", "3", "4", "5", "6", "7", "8"};
	std::vector<std::string> a(lols, lols + 5);
	ft::vector<std::string> a1(lols, lols + 5);

	a1.push_back(*(lols));
	ft::vector<std::string>::iterator it = a1.begin();
	for (;it != a1.end(); ++it){
		std::cout << *it << std::endl;
	}
//	ft::vector<int>		my1(kek, kek + 9);
//	std::vector<int>	orig(kek, kek + 9);
////	my1.reserve(100);
////	orig.reserve(100);
//
//	ft::vector<int>::iterator it(my1.begin() + 4);
//	std::vector<int>::iterator it_orig(orig.begin() + 4);
//	std::cout << my1.size() << " " << my1.capacity() <<" " << orig.size() << " " << orig.capacity() << std::endl;
////	my1.erase(it);
////	orig.erase(it_orig);
//	my1.clear();
//	orig.clear();
//	it = my1.begin();
//	it_orig = orig.begin();
//	for (;it != my1.end(); ++it, ++it_orig){
//		std::cout << *it << " " << *it_orig << std::endl;
//	}
//	std::cout << my1.size() << " " << my1.capacity() <<" " << orig.size() << " " << orig.capacity() << std::endl;

	return (0);
}