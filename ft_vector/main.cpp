#include <iostream>
#include <vector>
#include <array>
#include <list>
#include "vector.hpp"


int main() {

	int			kek[] = {8, 4,7,4,2,5,7,8,8,9, 10, 12, 13, 14 , 15, 16, 17, 18};
	std::string			a[10] = {"1", "2", "3","4", "5", "6","7", "8", "9"};
	ft::vector<std::string> a1(a, a + 8);
	ft::vector<ft::vector<std::string> > a2;
	a2.insert(a2.begin() ,a1);
//	std::vector<int> a2(kek, kek + 8);
//	std::sort(a1.begin(), a1.end());
//
//	std::vector<int>::const_iterator			it1 = a2.begin();
//	ft::vector<int>::const_iterator				it = a1.begin();
//	for (;it != a1.end(); ++it){
//		std::cout << *it << std::endl;
//	}
	return (0);
}