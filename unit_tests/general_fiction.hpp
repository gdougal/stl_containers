//
// Created by Gilberto Dougal on 5/22/21.
//

#ifndef CONTAINERS_GENERAL_FICTION_HPP
#define CONTAINERS_GENERAL_FICTION_HPP

#include <list>
#include <vector>
#include "gtest/gtest.h"
#include <string>
#include <stdexcept>

template<typename Container, typename std_Container>
class Ifill_behavior {
public:
	virtual void fill_rand(Container& my, std_Container& origin, int cnt_obj) = 0;
	virtual void fill_stable(Container& my, std_Container& origin, int cnt_obj) = 0;
};


template<class my_cont, class std_cont>
void	assert_containers_eq(const my_cont& my, const std_cont& orig) {
	typename std_cont::const_iterator	it_first = orig.begin();
	typename std_cont::const_iterator	it_second = orig.end();
	typename my_cont::const_iterator	it_ft_first = my.begin();
	typename my_cont::const_iterator	it_ft_second = my.end();
	for (; it_first != it_second; ) {
		EXPECT_EQ(*(it_first++), *(it_ft_first++));
	}
	EXPECT_EQ(it_ft_first, it_ft_second);
	EXPECT_EQ(my.empty(), orig.empty());
	EXPECT_EQ(my.size(), orig.size());
}


template<class my_cont, class std_cont>
class Generazed_test : public ::testing::Test {
protected:
	virtual void SetUp() {
		fill_object->fill_rand(ft_cont_rand_, orig_cont_rand_, size_);
		fill_object->fill_stable(ft_cont_filed_, orig_cont_filed_, size_);
	}

	std_cont	orig_cont_;
	my_cont			ft_cont_;

	std_cont	orig_cont_filed_;
	my_cont			ft_cont_filed_;

	std_cont	orig_cont_rand_;
	my_cont			ft_cont_rand_;

	int					size_;

	std::shared_ptr<Ifill_behavior<my_cont, std_cont> > fill_object;

	void	Check_sum_all() {
		assert_containers_eq(ft_cont_, orig_cont_);
		assert_containers_eq(ft_cont_, orig_cont_);
		assert_containers_eq(ft_cont_, orig_cont_);
	}
};


class TEST_CLASS {
private:
	int int_val;
	std::string str_val;
public:
	TEST_CLASS() : int_val(10), str_val(std::to_string(int_val)) {}
	TEST_CLASS(int a) : int_val(a), str_val(std::to_string(a)) {}
	TEST_CLASS(const TEST_CLASS& ref) {
		*this = ref;
	}

	TEST_CLASS& operator=(const TEST_CLASS& ref) {
		if (this != &ref) {
			int_val = ref.int_val;
			str_val.clear();
			str_val = ref.str_val;
		}
		return *this;
	}
	friend bool	operator==(const TEST_CLASS& lhs, const TEST_CLASS& rhs);

	std::pair<int&, std::string&>	operator*() {
		return {int_val, str_val};
	}
	virtual ~TEST_CLASS() {}
};

bool	operator==(const TEST_CLASS& lhs, const TEST_CLASS& rhs) {
	return (lhs.int_val == rhs.int_val && lhs.str_val == rhs.str_val);
}

bool	operator!=(const TEST_CLASS& lhs, const TEST_CLASS& rhs) {
	return !(lhs == rhs);
}

size_t random_size_t(size_t min, size_t max) {
	return  (max - min) * ((((size_t) rand()) / (size_t) RAND_MAX)) + min ;
}


#endif //CONTAINERS_GENERAL_FICTION_HPP
