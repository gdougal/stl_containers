#include <iostream>
#include "ft_map.hpp"
#include <map>
#include <vector>


//template<typename Map>
//void print_map(Map& m)
//{
//	std::cout << '{';
//	for(auto& p: m)
//		std::cout << p.first << ':' << p.second << ' ';
//	std::cout << "}\n";
//}
//
//struct Point { double x, y; };
//struct PointCmp {
//	bool operator()(const Point& lhs, const Point& rhs) const {
//		return lhs.x < rhs.x; // NB. intentionally ignores y
//	}
//};

int main() {
//	std::map<std::string, int> a;
//	std::pair<std::map<std::string, int>::iterator, bool> g = a.insert(std::pair<std::string, int>("sdf", 100));
//	std::pair<std::map<std::string, int>::iterator, bool> g1 = a.insert(std::pair<std::string, int>("sdf1", 100));
//	std::pair<std::map<std::string, int>::iterator, bool> g2 = a.insert(std::pair<std::string, int>("sdf", 1));

	ft::map<std::string, int> k;
	k.insert(std::pair<std::string, int>("a", 10));
	k.insert(std::pair<std::string, int>("s", 5));
	k.insert(std::pair<std::string, int>("d", 20));
//	ft::map<std::string, int>::iterator it(k.roooot_______());
//	std::cout << &*it << std::endl;
//	std::cout << it.operator->() << std::endl;
	return 0;
}