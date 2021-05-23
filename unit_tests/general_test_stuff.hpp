//
// Created by Gilberto Dougal on 5/23/21.
//

#ifndef CONTAINERS_GENERAL_TEST_STUFF_HPP
#define CONTAINERS_GENERAL_TEST_STUFF_HPP
#include "general_fiction.hpp"



template<class ft_cont, class std_cont>
void front(ft_cont& ft, std_cont& std) {
	assert_containers_eq(ft, std);
	while (!std.empty()) {
		EXPECT_EQ(ft.front(), std.front());
		ft.erase(ft.begin());
		std.erase(std.begin());
	}
	assert_containers_eq(ft, std);
}

template<class ft_cont, class std_cont>
void back(ft_cont& ft, std_cont& std) {
	assert_containers_eq(ft, std);
	while (!std.empty()) {
		EXPECT_EQ(ft.back(), std.back());
		ft.pop_back();
		std.pop_back();
	}
	assert_containers_eq(ft, std);
}

template<class ft_cont, class std_cont>
void assign(const ft_cont& ft, const std_cont& std, ft_cont ft_assign = ft_cont(), std_cont std_assign = std_cont()) {
	assert_containers_eq(ft, std);
	typename ft_cont::const_iterator ft_it_begin(ft.begin());
	typename std_cont::const_iterator std_it_begin(std.begin());
	for (; ft_it_begin != ft.end() && std_it_begin != std.end(); ++ft_it_begin, ++std_it_begin) {
		ft_assign.assign(ft_it_begin, ft.end());
		std_assign.assign(std_it_begin, std.end());
		assert_containers_eq(ft, std);
		ft_assign.assign((size_t)std::distance(ft_it_begin, ft.end()), ft.front());
		std_assign.assign((size_t)std::distance(ft_it_begin, ft.end()), ft.front());
		assert_containers_eq(ft, std);
	}
}

template<class ft_cont, class std_cont>
void push_back(ft_cont& ft, std_cont& std, ft_cont ft_assign = ft_cont(), std_cont std_assign = std_cont()) {
	assert_containers_eq(ft, std);
	typename ft_cont::iterator ft_it_begin(ft.begin());
	typename std_cont::iterator std_it_begin(std.begin());
	for (int i = 0; i != (int)std::distance(ft.begin(), ft.end()); ++i) {
		ft_assign.push_back(*ft_it_begin);
		std_assign.push_back(*std_it_begin);
		++ft_it_begin;
		++std_it_begin;
		assert_containers_eq(ft, std);
	}
}

template<class ft_cont, class std_cont>
void pop_back(ft_cont& ft, std_cont& std) {
	assert_containers_eq(ft, std);
	while (!ft.empty() && !std.empty()) {
		ft.pop_back();
		std.pop_back();
		assert_containers_eq(ft, std);
	}
}

template<class ft_cont, class std_cont>
void insert(ft_cont& ft, std_cont& std) {
	assert_containers_eq(ft, std);

	typename ft_cont::iterator ft_it;
	typename std_cont::iterator std_it;

	int tmp;
	while (ft.size() != 500 && std.size() != 500) {
		tmp = (rand()%1023);

		ft_it = ft.insert(ft.begin(), tmp);
		std_it = std.insert(std.begin(), tmp);
		assert_containers_eq(ft, std);
		EXPECT_EQ(*ft_it, *std_it);

		ft_it = ft.insert(ft.end(), tmp);
		std_it = std.insert(std.end(), tmp);
		assert_containers_eq(ft, std);
		EXPECT_EQ(*ft_it, *std_it);
	}
}

template<class ft_cont, class std_cont>
void insert_fill(ft_cont& ft, std_cont& std) {
	assert_containers_eq(ft, std);
	int tmp;
	size_t number;
	while (ft.size() > 1000 && std.size() > 1000) {
		tmp = (rand()%1023);
		number = (size_t)(rand()%30);
		ft.insert(ft.end(), number, tmp);
		std.insert(std.end(), number, tmp);
		assert_containers_eq(ft, std);
	}
}

template<class ft_cont, class std_cont>
void insert_range(ft_cont& ft, std_cont& std) {
	assert_containers_eq(ft, std);
	std_cont	range;
	size_t size = random_size_t(10, 100);
	while (range.size() < size) {
		range.push_back(rand() % 1023);
	}
	ft.insert(ft.end(), range.begin(), range.end());
	std.insert(std.end(), range.begin(), range.end());
	assert_containers_eq(ft, std);
}

template<class ft_cont, class std_cont>
void erase(ft_cont& ft, std_cont& std) {
	assert_containers_eq(ft, std);
	int tmp;
	typename ft_cont::iterator ft_it(ft.begin());
	typename std_cont::iterator std_it(std.begin());

	while (!ft.empty() && !std.empty()) {
		tmp = (rand()%(int)std.size());
		while(tmp--) {
			++ft_it;
			++std_it;
		}
		ft_it = ft.erase(ft.begin());
		std_it = std.erase(std.begin());
		assert_containers_eq(ft, std);
		if (ft_it != ft.end() || std_it != std.end())
			EXPECT_EQ(*ft_it, *std_it);
	}
}

template<class ft_cont, class std_cont>
void erase_range(ft_cont& ft, std_cont& std) {
	assert_containers_eq(ft, std);
	size_t tmp;
	typename ft_cont::iterator ft_it(ft.begin());
	typename std_cont::iterator std_it(std.begin());
	typename ft_cont::iterator ft_it_second(ft.begin());
	typename std_cont::iterator std_it_second(std.begin());

	tmp = random_size_t(0, ft.size()/2);
	while(tmp-- != 0) {
		++ft_it;
		++std_it;
	}
	ft_it_second = ft_it;
	std_it_second = std_it;
	tmp = random_size_t(ft.size()/2, ft.size() - 1);
	while(tmp-- != 0) {
		++ft_it_second;
		++std_it_second;
	}
	ft_it = ft.erase(ft_it, ft_it_second);
	std_it = std.erase(std_it, std_it_second);
	assert_containers_eq(ft, std);
	if (ft_it != ft.end() || std_it != std.end())
		EXPECT_EQ(*ft_it, *std_it);
}

template<class ft_cont, class std_cont>
void swap(ft_cont& ft, std_cont& std, ft_cont& ft_swp, std_cont& std_swp) {
	assert_containers_eq(ft, std);
	ft.swap(ft_swp);
	std.swap(std_swp);
	assert_containers_eq(ft, std);
}

template<class ft_cont, class std_cont>
void clear(ft_cont& ft, std_cont& std) {
	assert_containers_eq(ft, std);
	ft.clear();
	std.clear();
	assert_containers_eq(ft, std);
}

template<class ft_cont, class std_cont>
void resize(ft_cont& ft, std_cont& std, uint64_t new_size) {
	assert_containers_eq(ft, std);
	ft.resize(new_size);
	std.resize(new_size);
	assert_containers_eq(ft, std);
}

template<class ft_cont, class std_cont>
void resize_with_val(ft_cont& ft, std_cont& std, uint64_t new_size, int value) {
	assert_containers_eq(ft, std);
	ft.resize(new_size, value);
	std.resize(new_size, value);
	assert_containers_eq(ft, std);
}

#endif //CONTAINERS_GENERAL_TEST_STUFF_HPP
