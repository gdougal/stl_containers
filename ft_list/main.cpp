#include <iostream>
#include "ft_list.hpp"
#include <list>
#include <deque>


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

template<class CONT>
void lol(CONT* a) {
	ft::list<int> ref;
	for (int i = 0; i < 1000000; ++i) {
		ref.push_back(rand() % 23345);
	}
	(*a).assign(ref.begin(), ref.end());
}


int main() {
	srand(time(NULL));
	std::list<int> ref;

	for (int i = 0; i < 100000; ++i) {
		ref.push_back(rand() % 23345);
	}

	std::list<int> ref1;

	for (int i = 0; i < 20; ++i) {
		ref1.push_back(i);
	}

	ft::list<int> ref2;

	for (int i = 0; i < 20; ++i) {
		ref2.push_back(i);
	}

	std::list<int> orig_a; //(ref.begin(), ref.end());
	ft::list<int> a; //(ref.begin(), ref.end());
	lol<ft::list<int> >(&a);
	lol<std::list<int> >(&orig_a);


	orig_a.merge(ref1);
	a.merge(ref2);
	a.sort();
	orig_a.sort();
	print_both(orig_a, a);
//	print_my(a, a.begin());
//	print_orig(orig_a, orig_a.begin());
//	while (1);
	return 0;
}
