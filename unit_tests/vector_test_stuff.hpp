//
// Created by Gilberto Dougal on 5/22/21.
//

#ifndef CONTAINERS_VECTOR_TEST_STUFF_HPP
#define CONTAINERS_VECTOR_TEST_STUFF_HPP

template <typename T>
class fill_behavior_vector_int: public Ifill_behavior<ft::vector<T>, std::vector<T> > {
public:
fill_behavior_vector_int() = default;
void fill_rand(ft::vector<T>& my, std::vector<T>& origin, int cnt_obj) override {
int tmp;
for (int i = 0; i < cnt_obj; ++i) {
tmp = rand()%1000;
my.push_back(T(tmp));
origin.push_back(T(tmp));
}
}

void fill_stable(ft::vector<T>& my, std::vector<T>& origin, int cnt_obj) override {
for (int i = 0; i < cnt_obj; ++i) {
my.push_back(T(i));
origin.push_back(T(i));
}
}

virtual ~fill_behavior_vector_int() = default;
};


class Vector_test_int : public Generazed_test<ft::vector<int>, std::vector<int> > {
public:
Vector_test_int() {
	fill_object = std::shared_ptr<fill_behavior_vector_int<int> >(new fill_behavior_vector_int<int>);
	size_ = 100;
}
virtual ~Vector_test_int() = default;
};

class Vector_test_TEST_CLASS : public Generazed_test<ft::vector<TEST_CLASS>, std::vector<TEST_CLASS> > {
public:
Vector_test_TEST_CLASS() {
	fill_object = std::shared_ptr<fill_behavior_vector_int<TEST_CLASS> >(new fill_behavior_vector_int<TEST_CLASS>);
	size_ = 100;
}
virtual ~Vector_test_TEST_CLASS() = default;
};


typedef ft::vector<int> ft_vec_int;
typedef std::vector<int> std_vec_int;
typedef ft::vector<TEST_CLASS> ft_vec_class;
typedef std::vector<TEST_CLASS> std_vec_class;


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

template<class ft_cont, class std_cont>
void reserve(ft_cont& ft, std_cont& std, uint64_t new_size) {
	assert_containers_eq(ft, std);
	ft.reserve(new_size);
	std.reserve(new_size);
	assert_containers_eq(ft, std);
	EXPECT_EQ(ft.capacity(), std.capacity());
}

template<class ft_cont, class std_cont>
void acess(const ft_cont& ft, const std_cont& std) {
	assert_containers_eq(ft, std);
	for (uint64_t i = 0; i < std.size(); ++i) {
		EXPECT_EQ(ft[i], std[i]);
	}
	for (uint64_t i = 0; i < ft.size(); ++i) {
		EXPECT_EQ(ft[i], std[i]);
	}
	assert_containers_eq(ft, std);
}

template<class ft_cont, class std_cont>
void at(const ft_cont& ft, const std_cont& std) {
	assert_containers_eq(ft, std);
	for (uint64_t i = 0; i < std.size(); ++i) {
		EXPECT_EQ(ft.at(i), std.at(i));
	}
	for (uint64_t i = 0; i < ft.size(); ++i) {
		EXPECT_EQ(ft.at(i), std.at(i));
	}
	// WITH THROW :
	//ft.at(ft.size());
	//std.at(std.size());
	assert_containers_eq(ft, std);
}

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
	int tmp;
	while (ft.size() != 500 && std.size() != 500) {
		tmp = (rand()%1023);
		ft.insert(ft.begin(), tmp);
		std.insert(std.begin(), tmp);
		ft.insert(ft.begin(), tmp);
		std.insert(std.begin(), tmp);
		assert_containers_eq(ft, std);
	}
}

template<class ft_cont, class std_cont>
void insert_fill(ft_cont& ft, std_cont& std) {
	assert_containers_eq(ft, std);
	int tmp;
	size_t number;
	while (ft.size() != 1000 && std.size() != 1000) {
		tmp = (rand()%1023);
		number = 20;
		ft.insert(ft.end(), number, tmp);
		std.insert(std.end(), number, tmp);
		assert_containers_eq(ft, std);
	}
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
	tmp = random_size_t(ft.size()/2, ft.size());
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


#endif //CONTAINERS_VECTOR_TEST_STUFF_HPP
