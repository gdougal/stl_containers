#include <iostream>
#include "ft_list.hpp"
#include <list>
#include <vector>


void print_orig(std::list<int>& orig, std::list<int>::iterator it_param, bool endl = true) {
	if (endl)
		for (; it_param != orig.end(); ++it_param)
			std::cout << "Orig: " << (*it_param) << std::endl;
	else
		std::cout << "Orig: " << (*it_param) << "     ";
}

template <typename T>
void print_my(ft::list<T>& a, typename ft::list<T>::iterator it_param, bool endl = true) {
	if (endl)
		for (; it_param != a.end(); ++it_param)
			std::cout << "My: " << (*it_param) << std::endl;
	else
		std::cout << "My: " << (*it_param);

}

void print_both(std::list<int>& orig, ft::list<int>& my) {
	std::list<int>::iterator it_orig(orig.begin());
	ft::list<int>::iterator it_my(my.begin());


	for (;; ++it_orig, ++it_my) {
//		if (it_my == my.end())
//			break ;
		if (it_orig == orig.end())
			break ;
		if (it_orig != orig.end())
			print_orig(orig, it_orig, false);
		if (it_my != my.end())
			print_my(my, it_my, false);
		std::cout << std::endl;
	}
	std::cout << "Orig size: " << orig.size() << std::endl;
	std::cout << "My size: " << my.size() << std::endl;
}

bool	compare(int a, int b)
{
	return (b <= a);
}


int main() {
	srand(time(NULL));
//	std::list<int> ref;

//	for (int i = 0; i < 2; ++i) {
//		ref.push_back(rand() % 23345);
//	}

	std::list<int> ref1;

	for (int i = 0; i < 20; ++i) {
		ref1.push_back(i);
	}

	ft::list<int> ref2;

	for (int i = 0; i < 20; ++i) {
		ref2.push_back(i);
	}

//	std::list<int> orig_a(ref.begin(), ref.end());
//	ft::list<int> a(ref.begin(), ref.end());

	std::list<int> orig_a(5, 5);
	ft::list<int> a(5, 5);

//	orig_a.splice(orig_a.end(), ref1);
//	a.splice(a.end(), ref2);
	orig_a.merge(ref1);
	a.merge(ref2);
//	a.sort();
//	orig_a.sort();
//	print_both(orig_a, a);
//	print_my(a, a.begin());
//	print_orig(orig_a, orig_a.begin());
//	while (1);
	return 0;
}
