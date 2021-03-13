#include <iostream>
#include <vector>
#include <array>
#include <list>
#include "vector.hpp"


int main() {

	int			kek[] = {0, 1,2,3,4,5,6,7,8,9, 10, 12, 13, 14 , 15, 16, 17, 18};
	std::string	lols[8] = {"1", "2", "3", "4", "5", "6", "7", "8"};
	std::list<std::string> a(20, "1");
//	std::vector<int>::iterator it = orig.begin();
//	*it = 10;
//	std::cout << *it << std::endl;
//	ft::vector<int>		my(kek, kek + 4);
//	ft::vector<int>		my1(10, 1);
//	std::vector<int>	orig(10, 1);
	std::list<std::string>::iterator it3 = a.begin();
	std::list<std::string>::iterator it1 = a.end();
	std::vector<std::string>	orig1(it3, it1);
	ft::vector<std::string>		my2(it3, it1);
	ft::vector<std::string>		my3(lols, lols + 7);
//	std::cout << my.size() << " " << my.capacity() << " " << orig.size() << " " << orig.capacity() << std::endl;
//	my.push_back(10);
//	orig.push_back(10);
//	std::cout << my.size() << " " << my.capacity() << " " << orig.size() << " " << orig.capacity() << std::endl;
//	size_t l = my.capacity();
//	size_t l1 = orig.capacity();
//	for (int i = 0; i < 10000000; ++i) {
//		my.push_back(10);
//		orig.push_back(10);
//		if (my.capacity() > l || orig.capacity() > l1) {
//			std::cout << my.size() << " " << my.capacity() << " "<< orig.size() << " " << orig.capacity() << std::endl;
//			l = my.capacity();
//			l1 = orig.capacity();
//			my.pop_back();
//			orig.pop_back();
//		}
//	}
//	my1.push_back(10);
//	orig.push_back(10);

//	ft::vector<int>::iterator it(my1.begin() + 5);
//	std::vector<int>::iterator it_orig(orig.begin() + 5);
//	std::cout << &(*it) << " " << &my1[5] << std::endl;
//	std::cout << my1.size() << " " << my1.capacity() <<" " << orig.size() << " " << orig.capacity() << std::endl;
//	my1.insert(it, 10, 20);
//	orig.insert(it_orig, 10, 20);
//	it = my1.begin();
//	it_orig = orig.begin();
//	for (; it != my1.end() || it_orig != orig.end(); ++it, ++it_orig){
//		std::cout << *it << " " << *it_orig << std::endl;
//	}
//	std::cout << my1.size() << " " << my1.capacity() <<" " << orig.size() << " " << orig.capacity() << std::endl;

//	std::string kek1("lol");
//	orig1.push_back(kek1);
//	my2.push_back(kek1);
	ft::vector<std::string>::iterator it(my2.begin() + 5);
	std::vector<std::string>::iterator it_orig1(orig1.begin() + 5);
//	std::cout << &(*it) << " " << &my1[5] << std::endl;
//	std::cout << my1.size() << " " << my1.capacity() <<" " << orig.size() << " " << orig.capacity() << std::endl;
//	my2.insert(it, "20");
//	orig1.insert(it_orig1, "20");
	it = my2.begin();
	it_orig1 = orig1.begin();
	for (; it != my2.end() || it_orig1 != orig1.end(); ++it, ++it_orig1){
		std::cout << *it << " " << *it_orig1 << std::endl;
	}
//	std::cout << my2.size() << " " << my2.capacity() <<" " << orig1.size() << " " << orig1.capacity() << std::endl;
	return (0);
}