//
// Created by Gilberto Dougal on 5/23/21.
//

#ifndef CONTAINERS_LIST_TEST_STUFF_HPP
#define CONTAINERS_LIST_TEST_STUFF_HPP

#include "general_test_stuff.hpp"
#include "ft_list.hpp"

template <typename T>
class fill_behavior_list: public Ifill_behavior<ft::list<T>, std::list<T> > {
	public:
	fill_behavior_list() = default;
	void fill_rand(ft::list<T>& my, std::list<T>& origin, int cnt_obj) override {
		int tmp;
		for (int i = 0; i < cnt_obj; ++i) {
			tmp = rand()%1000;
			my.push_back(T(tmp));
			origin.push_back(T(tmp));
		}
	}

void fill_stable(ft::list<T>& my, std::list<T>& origin, int cnt_obj) override {
	for (int i = 0; i < cnt_obj; ++i) {
			my.push_back(T(i));
			origin.push_back(T(i));
		}
	}

	virtual ~fill_behavior_list() = default;
};


class List_test_int : public Generazed_test<ft::list<int>, std::list<int> > {
	public:
	List_test_int() {
		fill_object = std::make_shared<fill_behavior_list<int> >();
		size_ = 100;
	}
	virtual ~List_test_int() = default;
};

class List_test_TEST_CLASS : public Generazed_test<ft::list<TEST_CLASS>, std::list<TEST_CLASS> > {
	public:
	List_test_TEST_CLASS() {
		fill_object = std::make_shared<fill_behavior_list<TEST_CLASS> >();
		size_ = 100;
	}
	virtual ~List_test_TEST_CLASS() = default;
};

template<class ft_cont, class std_cont>
void splice_elem(ft_cont& ft, std_cont& std, ft_cont& ft_spliced, std_cont& std_spliced) {
	assert_containers_eq(ft, std);
	typename ft_cont::iterator ft_it_begin;
	typename std_cont::iterator std_it_begin;
	size_t pos;
	while (!ft_spliced.empty()) {
		ft_it_begin = ft_spliced.begin();
		std_it_begin = std_spliced.begin();
		pos = random_size_t(0, ft_spliced.size());
		for (size_t i = 0; i < pos; ++i) {
			++ft_it_begin;
			++std_it_begin;
		}
		ft.splice(ft.begin(), ft_spliced, ft_it_begin);
		std.splice(std.begin(), std_spliced, std_it_begin);
		assert_containers_eq(ft, std);
		assert_containers_eq(ft_spliced, std_spliced);
	}
}

template<class ft_cont, class std_cont>
void splice_list(ft_cont& ft, std_cont& std, ft_cont& ft_spliced, std_cont& std_spliced) {
	assert_containers_eq(ft, std);
	typename ft_cont::iterator ft_it_begin;
	typename std_cont::iterator std_it_begin;
	size_t pos;
	ft_it_begin = ft.begin();
	std_it_begin = std.begin();
	pos = random_size_t(0, ft.size());
	for (size_t i = 0; i < pos; ++i) {
		++ft_it_begin;
		++std_it_begin;
	}
	ft.splice(ft.begin(), ft_spliced);
	std.splice(std.begin(), std_spliced);
	assert_containers_eq(ft, std);
	assert_containers_eq(ft_spliced, std_spliced);
}

template<class ft_cont, class std_cont>
void splice_range(ft_cont& ft, std_cont& std, ft_cont& ft_spliced, std_cont& std_spliced) {
	assert_containers_eq(ft, std);
	size_t tmp;
	typename ft_cont::iterator ft_it_spl(ft_spliced.begin());
	typename std_cont::iterator std_it_spl(std_spliced.begin());
	typename ft_cont::iterator ft_it_second_spl(ft_spliced.begin());
	typename std_cont::iterator std_it_second_spl(std_spliced.begin());

	tmp = random_size_t(0, ft.size()/2);
	while(tmp-- != 0) {
		++ft_it_spl;
		++std_it_spl;
	}
	ft_it_second_spl = ft_it_spl;
	std_it_second_spl = std_it_spl;
	tmp = random_size_t(ft.size()/2, ft.size() - 1);
	while(tmp-- != 0) {
		++ft_it_second_spl;
		++std_it_second_spl;
	}

	typename ft_cont::iterator ft_it_begin;
	typename std_cont::iterator std_it_begin;
	size_t pos;
	ft_it_begin = ft.begin();
	std_it_begin = std.begin();
	pos = random_size_t(0, ft.size());
	for (size_t i = 0; i < pos; ++i) {
		++ft_it_begin;
		++std_it_begin;
	}
	ft.splice(ft.begin(), ft_spliced, ft_it_spl, ft_it_second_spl);
	std.splice(std.begin(), std_spliced, std_it_spl, std_it_second_spl);
	assert_containers_eq(ft, std);
	assert_containers_eq(ft_spliced, std_spliced);
}

template<class ft_cont, class std_cont, typename T>
void remove(ft_cont& ft, std_cont& std, T elem) {
	assert_containers_eq(ft, std);
	size_t pos;
	typename ft_cont::iterator ft_it_begin;
	typename std_cont::iterator std_it_begin;

	while (!ft.empty()) {
		pos = random_size_t(0, ft.size());
		ft_it_begin = ft.begin();
		for (size_t i = 0; i < pos; ++i) {
			++ft_it_begin;
		}
		elem = *ft_it_begin;
		ft.remove(elem);
		std.remove(elem);
		assert_containers_eq(ft, std);
	}
}



struct is_odd {
	bool operator() (const int& value) { return (value%2)==1; }
};

template<class ft_cont, class std_cont>
void remove_if(ft_cont& ft, std_cont& std) {
	assert_containers_eq(ft, std);
	ft.remove_if(is_odd());
	std.remove_if(is_odd());
	assert_containers_eq(ft, std);
}

template<class ft_cont, class std_cont>
void unique(ft_cont& ft, std_cont& std) {
	assert_containers_eq(ft, std);
	ft.unique();
	std.unique();
	assert_containers_eq(ft, std);
}

template<typename T>
struct is_not_equal {
	bool operator() (T first, T second)
	{ return first != second; }
};

template<class ft_cont, class std_cont, typename T>
void unique_with_binary_pred(ft_cont& ft, std_cont& std, T) {
	assert_containers_eq(ft, std);
	ft.unique(is_not_equal<T>());
	std.unique(is_not_equal<T>());
	assert_containers_eq(ft, std);
}

template<class ft_cont, class std_cont>
void merge(ft_cont& ft, std_cont& std, ft_cont& ft_merge, std_cont& std_merge) {
	assert_containers_eq(ft, std);
	ft.merge(ft_merge);
	std.merge(std_merge);
	assert_containers_eq(ft, std);
}

#endif //CONTAINERS_LIST_TEST_STUFF_HPP
